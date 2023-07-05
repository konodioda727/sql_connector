SET NAMES utf8;
SET CHARACTER SET utf8;
CREATE DATABASE market_managment;
USE market_managment;

CREATE TABLE Customers (
  customer_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  phone VARCHAR(20),
  email VARCHAR(100),
  address VARCHAR(200)
);

CREATE TABLE Stock (
  stock_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  income_price DECIMAL(10, 2),
  outcome_price DECIMAL(10, 2),
  stock INT
);


CREATE TABLE Employees (
  employee_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  phone VARCHAR(20),
  email VARCHAR(100)
);

CREATE TABLE Admin (
  admin_name VARCHAR(40) PRIMARY KEY,
  phone VARCHAR(20),
  email VARCHAR(100)
);

CREATE TABLE Products (
  product_id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(50),
  price DECIMAL(10, 2),
  stock INT
);

CREATE TABLE Orders (
  order_id INT PRIMARY KEY AUTO_INCREMENT,
  customer_id INT,
  employee_id INT,
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

-- 插入 Customers 表数据
INSERT INTO Customers (name, phone, email, address)
VALUES
  ('John Doe', '123456789', 'johndoe@example.com', '123 Main St'),
  ('Jane Smith', '987654321', 'janesmith@example.com', '456 Elm St');

-- 插入 Stock 表数据
INSERT INTO Stock (name, income_price, outcome_price, stock)
VALUES
  ('Product A', 10.50, 20.00, 100),
  ('Product B', 15.75, 30.00, 50);

-- 插入 Employees 表数据
INSERT INTO Employees (name, phone, email)
VALUES
  ('Employee 1', '555-123456', 'employee1@example.com'),
  ('Employee 2', '555-987654', 'employee2@example.com');

-- 插入 Admin 表数据
INSERT INTO Admin (admin_name, phone, email)
VALUES
  ('Admin 1', '555-555555', 'admin1@example.com');

-- 插入 Products 表数据
INSERT INTO Products (name, price, stock)
VALUES
  ('Product A', 20.00, 100),
  ('Product B', 30.00, 50);

-- 插入 Orders 表数据
INSERT INTO Orders (customer_id, employee_id, order_date, total_amount)
VALUES
  (1, 1, '2023-07-07', 150.00),
  (2, 2, '2023-07-08', 120.00);

-- 插入 Order_Items 表数据
INSERT INTO Order_Items (order_id, product_id, quantity)
VALUES
  (1, 1, 2),
  (1, 2, 3),
  (2, 1, 1);

