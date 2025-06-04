// BuyerDashboard.js
import React, { useEffect, useState, useContext, useCallback } from 'react';
import { Link } from 'react-router-dom';
import { AuthContext } from './App'; // Assuming App.js exports AuthContext

// Shared UI Components (could be imported)
function Button({ children, onClick, className = '', type = 'button', disabled = false }) {
  return (
    <button
      type={type}
      onClick={onClick}
      disabled={disabled}
      className={`px-4 py-2 bg-blue-500 text-white rounded shadow-md hover:bg-blue-600 focus:outline-none focus:ring-2 focus:ring-blue-300 disabled:bg-gray-300 disabled:cursor-not-allowed transition duration-150 ease-in-out ${className}`}
    >
      {children}
    </button>
  );
}

// --- Buyer Specific Tab Components ---

function BuyerStandsList() {
  const [stands, setStands] = useState([]);
  const { user } = useContext(AuthContext);
  const [message, setMessage] = useState({ text: '', type: '' });

  useEffect(() => {
    fetch('/stands/')
      .then(res => res.json())
      .then(data => setStands(data))
      .catch(err => {
        console.error("Failed to load stands:", err);
        setMessage({ text: "Could not load stands.", type: 'error'});
      });
  }, []);

  const handleAddToCart = async (productId) => {
    setMessage({ text: '', type: '' });
    if (!user || user.user_type !== 'buyer' || !user.details?.id) {
      setMessage({ text: 'Login as a buyer to add to cart.', type: 'error' });
      return;
    }
    try {
      const response = await fetch(`/buyers/${user.details.id}/cart/`, { // Trailing slash as per your main.py
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ product_id: productId }),
      });
      const responseData = await response.json();
      if (!response.ok) throw new Error(responseData.detail || 'Failed to add item.');
      setMessage({ text: responseData.message || 'Product added to cart!', type: 'success' });
    } catch (err) {
      setMessage({ text: err.message, type: 'error' });
    }
  };

  return (
    <div className="space-y-6">
      <h3 className="text-2xl font-semibold text-gray-700">Browse Available Stands</h3>
      {message.text && (
        <div className={`p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>
          {message.text}
        </div>
      )}
      {stands.length > 0 ? (
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
          {stands.map(s => (
            <div key={s.trader_id} className="border p-4 rounded-lg shadow-lg bg-white">
              <div className="flex justify-between items-center mb-3">
                <h4 className="text-xl font-bold text-indigo-600">{s.trader_name}</h4>
                <Link to={`/stand/${s.trader_id}`} className="text-sm text-indigo-500 hover:underline">View Full Stand &rarr;</Link>
              </div>
              <p className="text-gray-600 mb-2">Location: {s.location}</p>
              <p className="text-sm text-gray-500 mb-3">Products on stand: {s.products.length}</p>
              {s.products.length > 0 ? (
                <div className="space-y-2 max-h-48 overflow-y-auto pr-2 border-t pt-2">
                  {s.products.slice(0, 3).map(p => ( // Show a few products
                    <div key={p.product_id} className="border p-3 rounded-md bg-gray-50 flex justify-between items-center">
                      <div>
                        <p className="font-semibold text-sm">{p.name}</p>
                        <p className="font-medium text-gray-700 text-xs">Price: ${parseFloat(p.price).toFixed(2)}</p>
                      </div>
                      <Button onClick={() => handleAddToCart(p.product_id)} className="bg-green-500 hover:bg-green-600 text-xs px-2.5 py-1">
                        Add to Cart
                      </Button>
                    </div>
                  ))}
                  {s.products.length > 3 && <p className="text-xs text-center text-gray-500 mt-2">...and more</p>}
                </div>
              ) : <p className="text-gray-500 text-sm">No products currently on this stand.</p>}
            </div>
          ))}
        </div>
      ) : <p className="text-gray-500">No stands available at the moment.</p>}
    </div>
  );
}

function BuyerCartPage() {
  const { user, fetchAndUpdateUserDetails } = useContext(AuthContext);
  const [cart, setCart] = useState({ items: [], total: 0 });
  const [message, setMessage] = useState({text: '', type: ''});

  const fetchCart = useCallback(() => {
    if (!user || !user.details?.id) return;
    setMessage({text: '', type: ''});
    fetch(`/buyers/${user.details.id}/cart`)
      .then(res => {
        if (!res.ok) {
            res.json().then(err => setMessage({text: err.detail || 'Failed to load cart.', type: 'error'})).catch(()=>setMessage({text: 'Failed to load cart and parse error.', type: 'error'}));
            throw new Error('API error');
        }
        return res.json();
      })
      .then(data => setCart(data))
      .catch(err => {
        console.error('Cart load error:', err);
        if(!message.text && err.message !== 'API error') setMessage({text: 'Could not load your cart.', type: 'error'});
      });
  }, [user]);

  useEffect(() => {
    fetchCart();
  }, [fetchCart]);

  const handleCheckout = async () => {
    setMessage({text: '', type: ''});
    try {
      const response = await fetch(`/buyers/${user.details.id}/checkout/`, { method: 'POST' }); // Trailing slash
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || "Checkout failed.");
      setMessage({ text: data.message || `Paid $${parseFloat(data.amount_paid).toFixed(2)} successfully!`, type: 'success'});
      fetchCart();
      if (fetchAndUpdateUserDetails) fetchAndUpdateUserDetails();
    } catch (err) {
      setMessage({text: err.message, type: 'error'});
    }
  };

  const handleClearCart = async () => {
    setMessage({text: '', type: ''});
    try {
      const response = await fetch(`/buyers/${user.details.id}/cart`, { method: 'DELETE' });
      if (!response.ok && response.status !== 204) { // 204 is success for DELETE with no content
          const errData = await response.json().catch(()=> ({detail: "Failed to clear cart."}));
          throw new Error(errData.detail);
      }
      setMessage({ text: 'Cart cleared successfully.', type: 'success'});
      fetchCart();
    } catch (err) {
      setMessage({text: err.message, type: 'error'});
    }
  };

  return (
     <div className="space-y-6">
        <h3 className="text-2xl font-semibold text-gray-700">Your Shopping Cart</h3>
        {message.text && (
            <div className={`p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>
            {message.text}
            </div>
        )}
        {cart.items && cart.items.length > 0 ? (
        <>
            <div className="space-y-3 bg-white p-4 rounded-lg shadow">
            {cart.items.map((item, index) => (
                <div key={item.product.product_id || index} className="border-b last:border-b-0 py-3 flex justify-between items-center">
                <div>
                    <p className="font-semibold text-lg text-indigo-700">{item.product.name}</p>
                    {/* CartItemResponse no longer has negotiated_price */}
                    <p className="text-gray-600">Price: ${parseFloat(item.product.price).toFixed(2)}</p>
                    <p className="text-xs text-gray-400">Product ID: {item.product.product_id}</p>
                </div>
                </div>
            ))}
            </div>
            <div className="mt-6 pt-4 border-t flex flex-col items-end">
              <p className="text-2xl font-bold text-gray-800 mb-4">Total: ${parseFloat(cart.total).toFixed(2)}</p>
              <div className="flex space-x-3">
                  <Button onClick={handleClearCart} className="bg-red-500 hover:bg-red-600 px-6 py-2.5">Clear Cart</Button>
                  <Button onClick={handleCheckout} className="bg-green-600 hover:bg-green-700 px-6 py-2.5" disabled={cart.items.length === 0}>Proceed to Checkout</Button>
              </div>
            </div>
        </>
        ) : (
          <div className="text-center py-10">
            <svg className="mx-auto h-12 w-12 text-gray-400" fill="none" viewBox="0 0 24 24" stroke="currentColor" aria-hidden="true"><path vectorEffect="non-scaling-stroke" strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M3 3h2l.4 2M7 13h10l4-8H5.4M7 13L5.4 5M7 13l-2.293 2.293c-.63.63-.184 1.707.707 1.707H17m0 0a2 2 0 100 4 2 2 0 000-4zm-8 2a2 2 0 11-4 0 2 2 0 014 0z" /></svg>
            <h3 className="mt-2 text-sm font-medium text-gray-900">Your cart is empty</h3>
            <p className="mt-1 text-sm text-gray-500">Start adding some products!</p>
          </div>
        )}
    </div>
  );
}

function BuyerAdvertisementsList() {
  const [ads, setAds] = useState([]);
  useEffect(() => {
    fetch('/advertisements/?active_only=true')
      .then(res => res.json())
      .then(data => setAds(data))
      .catch(err => console.error("Failed to load advertisements:", err));
  }, []);

  return (
    <div className="space-y-6">
      <h3 className="text-2xl font-semibold text-gray-700">Current Advertisements</h3>
      {ads.length > 0 ? (
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
        {ads.map(ad => (
            <div key={ad.ad_id} className="border p-4 rounded-lg shadow-lg bg-gradient-to-r from-blue-50 to-indigo-50">
            <p className="text-lg font-semibold text-indigo-700 mb-2">{ad.description}</p>
            {ad.stand && (<p className="text-sm text-gray-600">From: <span className="font-medium">{ad.stand.trader_name}</span> at {ad.stand.location}</p>)}
             <p className="text-xs text-gray-400 mt-2">Ad ID: {ad.ad_id} (Cost to trader: ${parseFloat(ad.price).toFixed(2)})</p>
            </div>))}
        </div>
      ) : <p className="text-gray-500">No active advertisements at the moment.</p>}
    </div>
  );
}

function BuyerAttractionsPage() {
  const { user, fetchAndUpdateUserDetails } = useContext(AuthContext);
  const [attractions, setAttractions] = useState([]);
  const [message, setMessage] = useState({text: '', type: ''});

  const fetchAttractionsData = useCallback(() => {
     fetch('/attractions/')
      .then(res => res.json())
      .then(data => setAttractions(data))
      .catch(err => { console.error("Failed to load attractions:", err); setMessage({text: "Could not load attractions.", type: "error"}); });
  }, []);

  useEffect(() => { fetchAttractionsData(); }, [fetchAttractionsData]);

  const handleVisitAttraction = async (attractionId) => {
    setMessage({text: '', type: ''});
    if (!user || !user.details?.id) return setMessage({text: 'Please log in to visit attractions.', type: 'error'});
    try {
      // Your backend has /attractions/{attraction_id}/visit/ with buyer_id as query param
      const response = await fetch(`/attractions/${attractionId}/visit/?buyer_id=${user.details.id}`, { method: 'POST' });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || "Failed to visit attraction.");
      setMessage({ text: data.message || '🎉 Visited attraction successfully!', type: 'success'});
      if (fetchAndUpdateUserDetails) fetchAndUpdateUserDetails();
    } catch (err) {
      setMessage({text: err.message, type: 'error'});
    }
  };

  return (
    <div className="space-y-6">
        <h3 className="text-2xl font-semibold text-gray-700">Explore Attractions</h3>
        {message.text && (<div className={`p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>{message.text}</div>)}
        {attractions.length > 0 ? (
            <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
            {attractions.map(at => (
                <div key={at.attraction_id} className="border p-4 rounded-lg shadow-lg bg-white flex flex-col justify-between">
                <div>
                    <h4 className="text-xl font-semibold text-purple-600 mb-1">{at.name}</h4>
                    <p className="text-sm text-gray-500 mb-2">(ID: {at.attraction_id})</p>
                    <p className="text-gray-600 mb-2">{at.description}</p>
                    <p className="text-md font-medium text-gray-800">Ticket Price: ${parseFloat(at.ticket_price).toFixed(2)}</p>
                    <p className="text-sm text-gray-500">Offered by: {at.seller_name || "Unknown Seller"}</p>
                </div>
                <Button onClick={() => handleVisitAttraction(at.attraction_id)} className="w-full mt-4 bg-purple-500 hover:bg-purple-600">Visit Attraction</Button>
                </div>))}
            </div>
        ) : <p className="text-gray-500">No attractions available right now.</p>}
    </div>
  );
}

function BuyerDashboard() {
  const { user, fetchAndUpdateUserDetails } = useContext(AuthContext);
  const [activeTab, setActiveTab] = useState('stands');

  useEffect(() => {
    if (fetchAndUpdateUserDetails) fetchAndUpdateUserDetails();
  }, [fetchAndUpdateUserDetails]);

  const buyerTabsConfig = [
    { id: 'stands', name: 'Browse Stands', component: <BuyerStandsList /> },
    { id: 'cart', name: 'My Cart', component: <BuyerCartPage /> },
    { id: 'ads', name: 'Advertisements', component: <BuyerAdvertisementsList /> },
    { id: 'attractions', name: 'Attractions', component: <BuyerAttractionsPage /> },
  ];
  const CurrentTabComponent = buyerTabsConfig.find(tab => tab.id === activeTab)?.component;

  return (
    <div className="p-4 md:p-6 bg-gray-50 min-h-screen">
      <div className="flex flex-col sm:flex-row justify-between items-start sm:items-center mb-6 pb-4 border-b border-gray-300">
        <h2 className="text-2xl md:text-3xl font-bold text-gray-800 mb-2 sm:mb-0">Buyer Dashboard: {user.details?.name} (ID: {user.details?.id})</h2>
        {/* Balance is now shown in GlobalNavbar */}
      </div>
      <div className="mb-6 border-b border-gray-200"><nav className="flex flex-wrap -mb-px" aria-label="Tabs">{buyerTabsConfig.map(tab => (<button key={tab.id} onClick={() => setActiveTab(tab.id)} className={`whitespace-nowrap py-3 px-4 font-medium text-sm text-center border-b-2 focus:outline-none ${activeTab === tab.id ? 'border-indigo-500 text-indigo-600' : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'}`}>{tab.name}</button>))}</nav></div>
      <div className="mt-4">{CurrentTabComponent || <p>Select a section to view.</p>}</div>
    </div>
  );
}

export default BuyerDashboard;