// App.js
import BuyerDashboard from './BuyerDashboard';
import React, { useState, useEffect, useContext, useCallback } from 'react';
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Navigate,
  useNavigate,
  useParams,
  Link
} from 'react-router-dom';

// Simple UI-Components (Tailwind CSS)
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

function Input({ label, value, onChange, type = 'text', placeholder = '', step, min, id }) {
  return (
    <div className="mb-4">
      {label && <label htmlFor={id || label} className="block text-sm font-medium text-gray-700 mb-1">{label}</label>}
      <input
        id={id || label}
        type={type}
        value={value}
        onChange={e => onChange(e.target.value)}
        placeholder={placeholder}
        step={step}
        min={min}
        className="mt-1 block w-full border border-gray-300 rounded-md p-2 shadow-sm focus:ring-indigo-500 focus:border-indigo-500 sm:text-sm"
      />
    </div>
  );
}

// Authentication Context
export const AuthContext = React.createContext();

function AuthProviderWrapper({ children }) {
  const navigate = useNavigate();
  const [user, setUser] = useState(() => {
    const savedUser = localStorage.getItem('user');
    return savedUser ? JSON.parse(savedUser) : null;
  });

  const fetchAndUpdateUserDetails = useCallback(async () => {
    if (user && user.details?.id && user.user_type) {
      try {
        const endpoint = user.user_type === 'trader' ? `/traders/${user.details.id}` : `/buyers/${user.details.id}`;
        const res = await fetch(endpoint);
        if (res.ok) {
          const latestDetails = await res.json();
          const updatedUser = {
            ...user,
            details: {
              ...user.details,
              name: latestDetails.name,
              contact_info: latestDetails.contact_info,
              ...(user.user_type === 'trader' ? { capital: latestDetails.capital } : { balance: latestDetails.balance })
            }
          };
          localStorage.setItem('user', JSON.stringify(updatedUser));
          setUser(updatedUser);
        } else {
          console.warn("Could not refresh user details, backend returned:", res.status);
        }
      } catch (error) {
        console.error("Failed to refresh user details:", error);
      }
    }
  }, [user]);

  const login = async (contact_info) => {
    try {
      const response = await fetch('/login', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ contact_info }),
      });
      if (!response.ok) {
        const errorData = await response.json().catch(() => ({ detail: 'Login failed. Please check contact info.' }));
        throw new Error(errorData.detail || 'Login failed');
      }
      const loginData = await response.json(); // { user_type, id }

      const userDetailsEndpoint = loginData.user_type === 'trader'
        ? `/traders/${loginData.id}`
        : `/buyers/${loginData.id}`;

      const detailsResponse = await fetch(userDetailsEndpoint);
      if (!detailsResponse.ok) {
        const errDet = await detailsResponse.json().catch(() => ({}));
        throw new Error(errDet.detail || `Failed to fetch user details for ${loginData.user_type} ID ${loginData.id}.`);
      }
      const fullUserDetails = await detailsResponse.json();

      const completeUserObject = {
        user_type: loginData.user_type,
        details: {
          id: loginData.id,
          name: fullUserDetails.name,
          contact_info: fullUserDetails.contact_info,
          ...(loginData.user_type === 'trader' ? { capital: fullUserDetails.capital } : { balance: fullUserDetails.balance })
        }
      };

      localStorage.setItem('user', JSON.stringify(completeUserObject));
      setUser(completeUserObject);

      if (completeUserObject.user_type === 'trader') {
        navigate('/seller/products');
      } else {
        navigate('/buyer/stands');
      }
    } catch (err) {
      alert(`Login Error: ${err.message}`);
    }
  };

  const logout = useCallback(() => {
    localStorage.removeItem('user');
    setUser(null);
    navigate('/login');
  }, [navigate]);

  return (
    <AuthContext.Provider value={{ user, login, logout, fetchAndUpdateUserDetails }}>
      {children}
    </AuthContext.Provider>
  );
}

function LoginPage() {
  const [contact, setContact] = useState('');
  const { login } = useContext(AuthContext);
  const handleSubmit = (e) => {
    e.preventDefault();
    if (!contact.trim()) { alert("Please enter your contact information."); return; }
    login(contact);
  };
  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-100">
      <div className="p-8 max-w-md w-full bg-white rounded-xl shadow-xl">
        <h1 className="text-3xl font-bold text-center text-gray-700 mb-6">Marketplace Login</h1>
        <form onSubmit={handleSubmit}>
          <Input id="contactInfo" label="Enter Contact Info (Email/Phone)" value={contact} onChange={setContact} placeholder="e.g., user@example.com or 1234567890" />
          <Button type="submit" className="w-full mt-4 py-2.5 bg-indigo-600 hover:bg-indigo-700">Login</Button>
        </form>
        <div className="mt-6 text-center">
          <p className="text-gray-600 mb-2">Or register as:</p>
          <div className="flex justify-center gap-4">
            <Link to="/register-trader"><Button className="bg-green-500 hover:bg-green-600">Trader</Button></Link>
            <Link to="/register-buyer"><Button className="bg-yellow-500 hover:bg-yellow-600">Buyer</Button></Link>
          </div>
        </div>
      </div>
    </div>
  );
}

function TraderRegistrationPage() {
  const [name, setName] = useState('');
  const [contact_info, setContactInfo] = useState('');
  const [message, setMessage] = useState({ text: '', type: '' });
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    setMessage({ text: '', type: '' });
    if (!name.trim() || !contact_info.trim()) {
      setMessage({ text: 'Name and contact info are required.', type: 'error' });
      return;
    }
    try {
      const response = await fetch('/traders/', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ name, contact_info }),
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || 'Failed to create trader.');
      setMessage({ text: 'Trader registered successfully! You can now log in.', type: 'success' });
      setName(''); setContactInfo('');
      setTimeout(() => navigate('/login'), 2000);
    } catch (err) {
      setMessage({ text: err.message, type: 'error' });
    }
  };

  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-100">
      <div className="p-8 max-w-md w-full bg-white rounded-xl shadow-xl">
        <h1 className="text-3xl font-bold text-center text-gray-700 mb-6">Register as Trader</h1>
        {message.text && (
          <div className={`mb-4 p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>
            {message.text}
          </div>
        )}
        <form onSubmit={handleSubmit}>
          <Input label="Name" value={name} onChange={setName} />
          <Input label="Contact Info" value={contact_info} onChange={setContactInfo} />
          <Button type="submit" className="w-full mt-4 py-2.5 bg-indigo-600 hover:bg-indigo-700">Register Trader</Button>
        </form>
        <p className="mt-4 text-center">
          Already have an account? <Link to="/login" className="text-indigo-600 hover:underline">Login</Link>
        </p>
      </div>
    </div>
  );
}

function BuyerRegistrationPage() {
  const [name, setName] = useState('');
  const [contact_info, setContactInfo] = useState('');
  const [message, setMessage] = useState({ text: '', type: '' });
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    setMessage({ text: '', type: '' });
    if (!name.trim() || !contact_info.trim()) {
      setMessage({ text: 'Name and contact info are required.', type: 'error' });
      return;
    }
    try {
      const response = await fetch('/buyers/', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ name, contact_info }),
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || 'Failed to create buyer.');
      setMessage({ text: 'Buyer registered successfully! You can now log in.', type: 'success' });
      setName(''); setContactInfo('');
      setTimeout(() => navigate('/login'), 2000);
    } catch (err) {
      setMessage({ text: err.message, type: 'error' });
    }
  };

  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-100">
      <div className="p-8 max-w-md w-full bg-white rounded-xl shadow-xl">
        <h1 className="text-3xl font-bold text-center text-gray-700 mb-6">Register as Buyer</h1>
        {message.text && (
          <div className={`mb-4 p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>
            {message.text}
          </div>
        )}
        <form onSubmit={handleSubmit}>
          <Input label="Name" value={name} onChange={setName} />
          <Input label="Contact Info" value={contact_info} onChange={setContactInfo} />
          <Button type="submit" className="w-full mt-4 py-2.5 bg-indigo-600 hover:bg-indigo-700">Register Buyer</Button>
        </form>
        <p className="mt-4 text-center">
          Already have an account? <Link to="/login" className="text-indigo-600 hover:underline">Login</Link>
        </p>
      </div>
    </div>
  );
}

function GlobalNavbar() {
  const { user, logout } = useContext(AuthContext);
  if (!user) return null;
  return (
    <nav className="bg-gray-800 text-white shadow-lg">
      <div className="container mx-auto px-6 py-3 flex justify-between items-center">
        <Link to={user.user_type === 'trader' ? '/seller/products' : '/buyer/stands'} className="text-xl font-semibold hover:text-gray-300">Marketplace</Link>
        <div className="flex items-center">
          <span className="mr-4 text-sm sm:text-base">
            {user.details?.name || user.user_type} (ID: {user.details?.id})
            {user.user_type === 'trader' && typeof user.details?.capital === 'number' && ` - Capital: $${user.details.capital.toFixed(2)}`}
            {user.user_type === 'buyer' && typeof user.details?.balance === 'number' && ` - Balance: $${user.details.balance.toFixed(2)}`}
          </span>
          <Button onClick={logout} className="bg-red-500 hover:bg-red-600 px-3 py-1.5 text-sm">Logout</Button>
        </div>
      </div>
    </nav>
  );
}

function StandDetailPage() {
  const { trader_id } = useParams();
  const { user } = useContext(AuthContext);
  const [stand, setStand] = useState(null);
  const [message, setMessage] = useState({ text: '', type: '' });

  useEffect(() => {
    setMessage({ text: '', type: '' });
    fetch(`/traders/${trader_id}/stand`)
      .then(res => {
        if (!res.ok) {
          res.json()
            .then(err => setMessage({ text: err.detail || 'Failed to load stand details.', type: 'error' }))
            .catch(() => setMessage({ text: 'Failed to load stand details and parse error.', type: 'error' }));
          throw new Error('API error');
        }
        return res.json();
      })
      .then(data => setStand(data))
      .catch(err => {
        console.error("StandDetail fetch error:", err);
        if (!message.text && err.message !== 'API error') setMessage({ text: 'Could not fetch stand details.', type: 'error' });
      });
  }, [trader_id]);

  const handleAddToCart = async (productId) => {
    setMessage({ text: '', type: '' });
    if (!user || user.user_type !== 'buyer' || !user.details?.id) {
      setMessage({ text: 'You must be logged in as a buyer to add items to cart.', type: 'error' });
      return;
    }
    try {
      const response = await fetch(`/buyers/${user.details.id}/cart/`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ product_id: productId }),
      });
      const responseData = await response.json();
      if (!response.ok) throw new Error(responseData.detail || 'Failed to add item to cart.');
      setMessage({ text: responseData.message || 'Product added to cart!', type: 'success' });
    } catch (err) {
      setMessage({ text: err.message, type: 'error' });
    }
  };

  if (!stand && message.type === 'error') return <div className="p-4 text-red-600 bg-red-100 rounded-md text-center">{message.text}</div>;
  if (!stand) return <div className="p-4 text-center text-gray-500">Loading stand details...</div>;

  return (
    <div className="p-6 bg-gray-50 min-h-screen">
      <h2 className="text-3xl font-bold mb-2 text-gray-800">Stand: {stand.trader_name}</h2>
      <p className="text-lg text-gray-600 mb-6">Location: {stand.location}</p>
      {message.text && <div className={`my-4 p-3 rounded-md text-sm ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>{message.text}</div>}
      <h3 className="text-2xl font-semibold mt-4 mb-4 text-gray-700">Products on Stand:</h3>
      {stand.products && stand.products.length > 0 ? (
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {stand.products.map(p => (
            <div key={p.product_id} className="border p-4 rounded-lg shadow-lg bg-white transition-transform hover:scale-105">
              <h4 className="text-xl font-semibold text-blue-700 mb-1">{p.name}</h4>
              <p className="text-sm text-gray-500 mb-2">(ID: {p.product_id})</p>
              <p className="text-gray-600 mb-2">{p.description}</p>
              <p className="text-xl font-medium text-gray-800 mb-4">Price: ${parseFloat(p.price).toFixed(2)}</p>
              {user && user.user_type === 'buyer' && (
                <Button onClick={() => handleAddToCart(p.product_id)} className="w-full bg-green-500 hover:bg-green-600">Add to Cart</Button>
              )}
            </div>
          ))}
        </div>
      ) : <p className="text-gray-500">No products currently available on this stand.</p>}
    </div>
  );
}

function SellerDashboard() {
  const { user, fetchAndUpdateUserDetails } = useContext(AuthContext);
  const [activeTab, setActiveTab] = useState('products');
  const AD_DEFAULT_PRICE = 100.0;

  const [myInventory, setMyInventory] = useState([]);
  const [newProductForm, setNewProductForm] = useState({ name: '', description: '', price: '' });
  const [productPriceInputs, setProductPriceInputs] = useState({});

  const [myStand, setMyStand] = useState({ products: [], location: '', trader_name: '' });
  const [unassignedProducts, setUnassignedProducts] = useState([]);
  const [selectedInventoryProductForStand, setSelectedInventoryProductForStand] = useState('');

  const [myAds, setMyAds] = useState([]);
  const [newAdDescription, setNewAdDescription] = useState('');

  const [myAttractions, setMyAttractions] = useState([]);
  const [newAttractionForm, setNewAttractionForm] = useState({ name: '', description: '', ticket_price: '' });

  const [message, setMessage] = useState({ text: '', type: '' });

  const clearMessage = () => setMessage({ text: '', type: '' });
  const showSuccess = (text) => setMessage({ text, type: 'success' });
  const showError = (text) => { console.error("Frontend Error:", text); setMessage({ text, type: 'error' }); }

  const fetchSellerData = useCallback(async () => {
    if (!user || !user.details?.id) return;
    clearMessage();
    try {
      const traderId = user.details.id;
      const [invRes, standRes, unassignedRes, adsRes, attractionsRes] = await Promise.all([
        fetch(`/traders/${traderId}/products`),
        fetch(`/traders/${traderId}/stand`),
        fetch(`/traders/${traderId}/stand/unassigned-products`),
        fetch('/advertisements/?active_only=false'),
        fetch('/attractions/')
      ]);

      if (!invRes.ok) { const err = await invRes.json().catch(() => ({})); throw new Error(err.detail || 'Failed to load inventory'); }
      setMyInventory(await invRes.json());

      if (!standRes.ok) { const err = await standRes.json().catch(() => ({})); throw new Error(err.detail || 'Failed to load stand data'); }
      setMyStand(await standRes.json());

      if (!unassignedRes.ok) { const err = await unassignedRes.json().catch(() => ({})); throw new Error(err.detail || 'Failed to load unassigned products'); }
      setUnassignedProducts(await unassignedRes.json());

      if (!adsRes.ok) { const err = await adsRes.json().catch(() => ({})); throw new Error(err.detail || 'Failed to load advertisements'); }
      const allAdsData = await adsRes.json();
      setMyAds(allAdsData.filter(ad => ad.stand?.trader_name === user.details.name));

      if (!attractionsRes.ok) { const err = await attractionsRes.json().catch(() => ({})); throw new Error(err.detail || 'Failed to load attractions'); }
      const allAttractionsData = await attractionsRes.json();
      setMyAttractions(allAttractionsData.filter(at => at.seller_id === traderId));
    } catch (err) {
      showError(err.message);
    }
  }, [user]);

  useEffect(() => {
    fetchSellerData();
  }, [fetchSellerData]);

  const handleNewProductChange = (field, value) => setNewProductForm(prev => ({ ...prev, [field]: value }));
  const handlePriceInputChange = (productId, value) => setProductPriceInputs(prev => ({ ...prev, [productId]: value }));

  const handleCreateProduct = async () => {
    clearMessage();
    if (!newProductForm.name || !newProductForm.price) return showError("Product name and price are required.");
    const price = parseFloat(newProductForm.price);
    if (isNaN(price) || price <= 0) return showError("Price must be a positive number.");

    try {
      const response = await fetch(`/traders/${user.details.id}/products/`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ...newProductForm, price: price }),
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || "Failed to create product.");
      fetchSellerData();
      setNewProductForm({ name: '', description: '', price: '' });
      showSuccess("Product created and added to inventory!");
    } catch (err) { showError(err.message); }
  };

  const handleUpdateProductPrice = async (productId) => {
    clearMessage();
    const newPriceStr = productPriceInputs[productId];
    if (!newPriceStr) return showError("Please enter a new price.");
    const newPrice = parseFloat(newPriceStr);
    if (isNaN(newPrice) || newPrice <= 0 || newPrice > 2000) {
      return showError("Price must be a number greater than 0 and no more than 2000.");
    }
    try {
      const response = await fetch(`/products/${productId}/price/?new_price=${newPrice}`, {
        method: 'PUT',
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || data.message || "Failed to update price.");
      fetchSellerData();
      setProductPriceInputs(prev => ({ ...prev, [productId]: '' }));
      showSuccess(data.message || "Product price updated!");
    } catch (err) { showError(err.message); }
  };

  // --- Stand Management ---
  const handleAddProductToStand = async () => {
    clearMessage();
    if (!selectedInventoryProductForStand) return showError("Please select a product from your inventory.");
    const productId = parseInt(selectedInventoryProductForStand);
    try {
      const response = await fetch(`/traders/${user.details.id}/stand/products/${productId}`, {
        method: 'POST',
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || data.message || "Failed to add product to stand.");
      fetchSellerData();
      setSelectedInventoryProductForStand('');
      showSuccess(data.message || "Product added to stand!");
    } catch (err) { showError(err.message); }
  };

  const handleRemoveProductFromStand = async (productId) => {
    clearMessage();
    try {
      const response = await fetch(`/traders/${user.details.id}/stand/products/${productId}`, {
        method: 'DELETE'
      });
      const data = await response.json();
      if (!response.ok && response.status !== 204) throw new Error(data.detail || data.message || "Failed to remove product from stand.");
      fetchSellerData();
      showSuccess(data.message || "Product removed from stand.");
    } catch (err) { showError(err.message); }
  };

  const handlePermanentDeleteProduct = async (productId) => {
    clearMessage();
    if (!window.confirm("Are you sure you want to PERMANENTLY delete this product from the entire system?")) {
      return;
    }
    showError("Note: Permanent product deletion endpoint (`DELETE /products/{product_id}`) needs to be fully implemented on backend and integrated here if it's different from stand removal.");
     try {
      const res = await fetch(`/traders/${user.details.id}/inventory/${productId}`, { method: 'DELETE' });
      if (!res.ok && res.status !== 204) {
        const errData = await res.json().catch(() => ({}));
        throw new Error(errData.detail || `Failed to permanently delete product. Status: ${res.status}`);
       }
       fetchSellerData();
       showSuccess("Product permanently deleted.");
     } catch (err) { showError(err.message); }
  };

  const handleCreateAd = async () => {
    clearMessage();
    if (!newAdDescription.trim()) return showError("Ad description cannot be empty.");
    try {
      const response = await fetch(`/advertisements/`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ description: newAdDescription, trader_id: user.details.id })
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || "Failed to create advertisement.");
      fetchSellerData();
      if (fetchAndUpdateUserDetails) fetchAndUpdateUserDetails();
      setNewAdDescription('');
      showSuccess("Advertisement created!");
    } catch (err) { showError(err.message); }
  };

  const handleNewAttractionChange = (field, value) => setNewAttractionForm(prev => ({ ...prev, [field]: value }));
  const handleCreateAttraction = async () => {
    clearMessage();
    if (!newAttractionForm.name || !newAttractionForm.ticket_price) return showError("Attraction name and ticket price are required.");
    const ticketPrice = parseFloat(newAttractionForm.ticket_price);
    if (isNaN(ticketPrice) || ticketPrice < 0) return showError("Invalid ticket price.");
    try {
      const response = await fetch(`/attractions/`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          ...newAttractionForm,
          ticket_price: ticketPrice,
          seller_id: user.details.id
        })
      });
      const data = await response.json();
      if (!response.ok) throw new Error(data.detail || "Failed to create attraction.");
      fetchSellerData();
      setNewAttractionForm({ name: '', description: '', ticket_price: '' });
      showSuccess("Attraction created!");
    } catch (err) { showError(err.message); }
  };

  // Swap the order of 'Advertisements' and 'Attractions' tabs
  const sellerTabs = [
    { name: 'My Inventory', id: 'products' },
    { name: 'My Stand', id: 'stand' },
    { name: 'Attractions', id: 'attractions' },
    { name: 'Advertisements', id: 'ads' },
  ];

  return (
    <div className="p-4 md:p-6 bg-gray-100 min-h-screen">
      <h2 className="text-2xl md:text-3xl font-bold mb-6 text-gray-800">Seller Dashboard: {user.details?.name} (ID: {user.details?.id})</h2>
      {message.text && <div className={`mb-4 p-3 rounded-md text-sm shadow ${message.type === 'success' ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>{message.text}</div>}
      <div className="mb-6 border-b border-gray-300">
        <nav className="flex flex-wrap -mb-px">
          {sellerTabs.map(tab => (
            <button
              key={tab.id}
              onClick={() => setActiveTab(tab.id)}
              className={`py-3 px-4 font-medium text-sm md:text-base text-center focus:outline-none whitespace-nowrap ${
                activeTab === tab.id
                  ? 'border-b-2 border-indigo-500 text-indigo-600'
                  : 'text-gray-500 hover:text-gray-700 hover:border-gray-400'
              }`}
            >
              {tab.name}
            </button>
          ))}
        </nav>
      </div>
      <div className="mt-2">
        {activeTab === 'products' && (
          <section className="space-y-6">
            <div className="p-6 bg-white shadow-xl rounded-lg">
              <h3 className="text-xl font-semibold mb-4 text-gray-700">Manage Your Inventory</h3>
              {myInventory.length > 0 ? myInventory.map(p => (
                <div key={p.product_id} className="border p-4 mb-4 rounded-md shadow-sm bg-gray-50">
                  <div className="flex flex-col md:flex-row justify-between md:items-center mb-2">
                    <h4 className="text-lg font-semibold text-indigo-700">{p.name} (ID: {p.product_id})</h4>
                    <p className="text-md font-medium text-gray-800">Current Price: ${parseFloat(p.price).toFixed(2)}</p>
                  </div>
                  <p className="text-sm text-gray-600 mb-3">{p.description}</p>
                  <div className="flex flex-col sm:flex-row items-stretch sm:items-end gap-3 mt-2">
                    <div className="flex-grow">
                      <Input
                        id={`price-${p.product_id}`}
                        value={productPriceInputs[p.product_id] || ''}
                        onChange={val => handlePriceInputChange(p.product_id, val)}
                        type="number"
                        placeholder={`New Price (current $${parseFloat(p.price).toFixed(2)})`}
                        step="0.01"
                        min="0.01"
                      />
                    </div>
                    <Button onClick={() => handleUpdateProductPrice(p.product_id)} className="w-full sm:w-auto bg-green-500 hover:bg-green-600 text-sm py-2">Update Price</Button>
                    <Button onClick={() => handlePermanentDeleteProduct(p.product_id)} className="w-full sm:w-auto bg-red-700 hover:bg-red-800 text-sm py-2">Delete Permanently</Button>
                  </div>
                </div>
              )) : <p className="text-gray-500">Your inventory is empty.</p>}
            </div>
            <div className="mt-6 p-6 bg-white shadow-xl rounded-lg border-t">
              <h4 className="text-xl font-semibold mb-3 text-gray-700">Create New Product for Inventory</h4>
              <div className="space-y-3">
                <Input label="Product Name" value={newProductForm.name} onChange={val => handleNewProductChange('name', val)} />
                <Input label="Description" value={newProductForm.description} onChange={val => handleNewProductChange('description', val)} />
                <Input label="Price" value={newProductForm.price} onChange={val => handleNewProductChange('price', val)} type="number" step="0.01" min="0.01" />
                <Button onClick={handleCreateProduct} className="w-full sm:w-auto bg-indigo-600 hover:bg-indigo-700">Add to Inventory</Button>
              </div>
            </div>
          </section>
        )}

        {activeTab === 'stand' && (
          <section className="space-y-6">
            <div className="p-6 bg-white shadow-xl rounded-lg">
              <h3 className="text-xl font-semibold mb-4 text-gray-700">Products Currently on Your Stand ({myStand.location || 'N/A'})</h3>
              {myStand.products && myStand.products.length > 0 ? myStand.products.map(p => (
                <div key={p.product_id} className="border p-3 mb-3 rounded-md shadow-sm bg-gray-50 flex justify-between items-center">
                  <div>
                    <p className="text-lg font-semibold text-indigo-700">{p.name} (ID: {p.product_id})</p>
                    <p className="text-gray-600">Price: ${parseFloat(p.price).toFixed(2)}</p>
                  </div>
                  <Button onClick={() => handleRemoveProductFromStand(p.product_id)} className="bg-red-500 hover:bg-red-600 text-sm py-1.5 px-3">Remove from Stand</Button>
                </div>
              )) : <p className="text-gray-500">Your stand is currently empty.</p>}
            </div>
            <div className="mt-6 p-6 bg-white shadow-xl rounded-lg border-t">
              <h4 className="text-xl font-semibold mb-3 text-gray-700">Add Product from Inventory to Stand</h4>
              {unassignedProducts.length > 0 ? (
                <div className="flex flex-col sm:flex-row items-end gap-3">
                  <div className="flex-grow">
                    <label htmlFor="productToAddToStand" className="block text-sm font-medium text-gray-700 mb-1">Select Product (Not on Stand):</label>
                    <select
                      id="productToAddToStand"
                      value={selectedInventoryProductForStand}
                      onChange={e => setSelectedInventoryProductForStand(e.target.value)}
                      className="mt-1 block w-full border border-gray-300 rounded-md p-2 shadow-sm focus:ring-indigo-500 focus:border-indigo-500 sm:text-sm"
                    >
                      <option value="">-- Choose a product --</option>
                      {unassignedProducts.map(p => (
                        <option key={p.product_id} value={p.product_id}>
                          {p.name} (${parseFloat(p.price).toFixed(2)})
                        </option>
                      ))}
                    </select>
                  </div>
                  <Button onClick={handleAddProductToStand} disabled={!selectedInventoryProductForStand} className="w-full sm:w-auto bg-green-500 hover:bg-green-600">Add to Stand</Button>
                </div>
              ) : (
                <p className="text-gray-500">All your inventory items are already on the stand, or your inventory is empty.</p>
              )}
            </div>
          </section>
        )}

        {activeTab === 'attractions' && (
          <section className="space-y-6">
            {/* Create Attraction Form moved above existing list */}
            <div className="mt-6 p-6 bg-white shadow-xl rounded-lg border-t">
              <h4 className="text-xl font-semibold mb-3 text-gray-700">Create New Attraction</h4>
              <div className="space-y-3">
                <Input label="Attraction Name" value={newAttractionForm.name} onChange={val => handleNewAttractionChange('name', val)} />
                <Input label="Description" value={newAttractionForm.description} onChange={val => handleNewAttractionChange('description', val)} />
                <Input label="Ticket Price" value={newAttractionForm.ticket_price} onChange={val => handleNewAttractionChange('ticket_price', val)} type="number" step="0.01" min="0" />
                <Button onClick={handleCreateAttraction} className="w-full sm:w-auto bg-indigo-600 hover:bg-indigo-700">Create Attraction</Button>
              </div>
            </div>

            <div className="p-6 bg-white shadow-xl rounded-lg">
              <h3 className="text-xl font-semibold mb-4 text-gray-700">Your Attractions</h3>
              {myAttractions.length > 0 ? myAttractions.map(at => (
                <div key={at.attraction_id} className="border p-3 mb-3 rounded-md shadow-sm bg-gray-50">
                  <p className="text-lg font-semibold text-indigo-700">{at.name} (ID: {at.attraction_id})</p>
                  <p className="text-gray-600 mb-1">{at.description}</p>
                  <p className="text-md font-medium text-gray-800">Ticket Price: ${parseFloat(at.ticket_price).toFixed(2)}</p>
                </div>
              )) : <p className="text-gray-500">You have no attractions.</p>}
            </div>
          </section>
        )}

        {activeTab === 'ads' && (
          <section className="space-y-6">
            {/* Create Advertisement Form moved above existing list */}
            <div className="mt-6 p-6 bg-white shadow-xl rounded-lg border-t">
              <h4 className="text-xl font-semibold mb-3 text-gray-700">Create New Advertisement</h4>
              <Input label="Ad Description" value={newAdDescription} onChange={setNewAdDescription} />
              <Button onClick={handleCreateAd} className="w-full sm:w-auto bg-indigo-600 hover:bg-indigo-700">Create Ad (Cost: ${AD_DEFAULT_PRICE.toFixed(2)})</Button>
            </div>

            <div className="p-6 bg-white shadow-xl rounded-lg">
              <h3 className="text-xl font-semibold mb-4 text-gray-700">Your Advertisements</h3>
              {myAds.length > 0 ? myAds.map(ad => (
                <div key={ad.ad_id} className="border p-3 mb-3 rounded-md shadow-sm bg-gray-50">
                  <p className="text-lg font-semibold text-indigo-700">{ad.description}</p>
                  <p className="text-gray-600">Cost: ${parseFloat(ad.price).toFixed(2)}</p>
                  <p className={`text-sm font-medium ${ad.is_active ? 'text-green-600' : 'text-red-600'}`}>Status: {ad.is_active ? 'Active' : 'Expired'}</p>
                  {ad.stand && <p className="text-xs text-gray-500">Linked to: {ad.stand.trader_name} at {ad.stand.location}</p>}
                </div>
              )) : <p className="text-gray-500">You have no advertisements.</p>}
            </div>
          </section>
        )}
      </div>
    </div>
  );
}

function App() {
  return (
    <Router>
      <AuthProviderWrapper>
        <GlobalNavbar />
        <main className="container mx-auto px-2 py-4 sm:px-4">
          <Routes>
            <Route path="/login" element={<LoginPage />} />
            <Route path="/register-trader" element={<TraderRegistrationPage />} />
            <Route path="/register-buyer" element={<BuyerRegistrationPage />} />
            <Route path="/stand/:trader_id" element={<PrivateRoute><StandDetailPage /></PrivateRoute>} />
            <Route path="/buyer/*" element={<PrivateRoute type="buyer"><BuyerDashboard /></PrivateRoute>} />
            <Route path="/seller/*" element={<PrivateRoute type="trader"><SellerDashboard /></PrivateRoute>} />
            <Route path="/" element={<Navigate to="/login" replace />} />
            <Route path="*" element={
              <div className="text-center p-10">
                <h1 className="text-3xl font-bold">404 - Page Not Found</h1>
                <p className="mt-4">The page you are looking for does not exist.</p>
                <Link to="/login" className="text-blue-500 hover:underline mt-6 inline-block">Go to Login</Link>
              </div>
            } />
          </Routes>
        </main>
      </AuthProviderWrapper>
    </Router>
  );
}

function PrivateRoute({ children, type }) {
  const { user } = useContext(AuthContext);
  if (!user || !user.details) return <Navigate to="/login" replace />;
  if (type && user.user_type !== type) return <Navigate to="/login" replace />;
  return children;
}

export default App;
