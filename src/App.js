import { useState } from 'react';

export default function Form() {
  const [num1, setnum1] = useState(0);
  const [num2, setnum2] = useState(0);
  const [product, setproduct] = useState(0);

  function handleNum1Change(e) {
    setnum1(e.target.value);
    setproduct(e.target.value * num2);
  }

  function handleNum2Change(e) {
    setnum2(e.target.value);
    setproduct(num1 * e.target.value);
  }

  return (
    <>
      <h2>Calculate the product</h2>
      <label>
        Number1:{''}
        <input
          value={num1}
          onChange={handleNum1Change}
        />
      </label>
      <label>
        Number2:{''}
        <input
          value={num2}
          onChange={handleNum2Change}
        />
      </label>
      <p>
        The product is: <b>{product}</b>
      </p>
    </>
  );
}
