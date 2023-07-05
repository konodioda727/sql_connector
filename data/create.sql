SET NAMES utf8;
SET CHARACTER SET utf8;

CREATE TABLE Customers (
  customer_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  phone VARCHAR(20),
  email VARCHAR(100),
  address VARCHAR(200)
);

CREATE TABLE Employees (
  employee_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  phone VARCHAR(20),
  email VARCHAR(100)
);

CREATE TABLE Products (
  product_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  price DECIMAL(10, 2),
  stock INT
);

CREATE TABLE Orders (
  order_id INT PRIMARY KEY AUTO_INCREMENT,
  customer_id INT,
  order_date DATE,
  total_amount DECIMAL(10, 2),
  FOREIGN KEY (customer_id) REFERENCES Customers(customer_id),
  FOREIGN KEY (employee_id) REFERENCES Employees(employee_id)
);

CREATE TABLE Order_Items (
  order_item_id INT PRIMARY KEY AUTO_INCREMENT,
  order_id INT,
  product_id INT,
  quantity INT,
  FOREIGN KEY (order_id) REFERENCES Orders(order_id),
  FOREIGN KEY (product_id) REFERENCES Products(product_id)
);




INSERT INTO Customers (name, phone, email, address)
VALUES ('John Doe', '1234567890', 'john@example.com', '123 Main St'),
       ('Jane Smith', '9876543210', 'jane@example.com', '456 Elm St');

INSERT INTO Products (name, price, stock)
VALUES ('apple', 1.99, 100),
       ('Banana', 0.99, 200),
       ('Orange', 2.49, 150);

INSERT INTO Orders (customer_id, order_date, total_amount)
VALUES (1, '2023-07-05', 15.99),
       (2, '2023-07-06', 10.49);

INSERT INTO Order_Items (order_id, product_id, quantity, item_price)
VALUES (1, 1, 5),
       (1, 2, 3),
       (2, 1, 2),
       (2, 3, 1);

INSERT INTO Employees (name, phone, email)
VALUES ('Robert Johnson', '555-1234', 'robert@example.com'),
       ('Mary Davis', '555-5678', 'mary@example.com');

