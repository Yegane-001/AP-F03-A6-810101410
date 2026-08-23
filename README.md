# UTaste 🍽️

**UTaste** is a multi-phase restaurant discovery & reservation system built in modern **C++20**, progressing from a command-line backend to a full **client-server web application**. The project was developed incrementally across three phases, applying object-oriented design, inheritance/polymorphism, and network programming concepts at each stage.

> *"Where Code Meets Cuisine"*

---

## 📌 Overview

UTaste lets users:
- Browse restaurants and their menus, sorted by proximity to the user's district (BFS-based neighborhood traversal)
- Reserve tables for a specific time range and optionally order food
- View, filter, and cancel their own reservations
- Manage a personal wallet, with restaurant-defined discounts (per-item, first-order, and total-order discounts) automatically applied at checkout
- Interact with the system either via a **command-line interface** (Phase 1 & 2) or a **browser-based web UI** (Phase 3)

## 🧩 Project Phases

### Phase 1 — Core Reservation Engine (CLI)
- Reads restaurant and district data from CSV files
- Implements a command-based interface (`GET` / `POST` / `PUT` / `DELETE`) simulating REST-style semantics over stdin
- User signup/login/logout with session-aware permission handling
- District-based restaurant discovery using neighborhood adjacency (BFS ordering)
- Table reservation with time-conflict detection, per-restaurant working hours, and menu-based food ordering
- Viewing and deleting reservations, with error handling via structured response codes (`OK`, `Not Found`, `Bad Request`, `Permission Denied`, `Empty`)

### Phase 2 — OOP Extensions: Discounts & Wallet
- Introduces a **wallet system**: users top up and spend virtual balance on reservations
- Adds a discount engine built around **inheritance and polymorphism**:
  - Per-item discounts (applied per matching order line)
  - First-order discounts (applied once, on a user's first order per restaurant)
  - Total-order-amount discounts (threshold-based, applied last)
  - Each discount type supports both **percentage-based** and **flat-amount** modes
- Discount configuration loaded from a dedicated CSV file per restaurant
- Reservation and detail-view commands extended to report original price, per-discount breakdown, total discount, and final payable amount

### Phase 3 — Web Server & Browser UI
- Reimplements the client-server interaction over **HTTP**, using the provided `APHTTP` library
- Full web front-end (HTML, with optional CSS/JS for bonus points) covering:
  - Signup / login pages with server-managed session IDs
  - Home page with navigation to all features
  - Restaurant listing & detail pages (menus, tables, discounts)
  - Reservation page (table, time range, food selection)
  - "My reservations" page across all restaurants
  - Logout available from every page
- Same underlying business logic from Phases 1 & 2, now decoupled from the CLI and driven by HTTP requests from a browser acting as the client

## 🛠️ Built With

- **C++20**
- APHTTP — lightweight HTTP server library (provided for the course)
- HTML / CSS / JavaScript (Phase 3 front-end)
- `make` / Makefile-based multi-file build system

## 🏗️ Design Highlights

- Object-oriented architecture with clear separation between **business logic** and **I/O / interface layers**, enabling the same core logic to be reused across the CLI (Phases 1–2) and the web server (Phase 3)
- Discount mechanisms modeled through a class hierarchy leveraging **inheritance and polymorphism**, avoiding duplicated logic across discount types
- Encapsulated command-handling classes, one per operation, keeping parsing/validation isolated from domain logic
- Consistent error-handling philosophy across phases (`Bad Request`, `Not Found`, `Permission Denied`, `Empty`, `OK`)


**Restaurants:**
```
name,district,foods:prices,opening_time,closing_time,number_of_tables
sib,Shariati,pitza:220;berger:190;hotdog:185,9,23,45
```

**Districts:**
```
district,neighbors
Azadi,Behboodi;SatarKhan;Shadman
```

**Discounts:**
```
restaurant_name,total_price_discount,first_order_discount,food_discount
sib,percent;800;7,none,amount;burger:20|percent;pizza:50
```


*(Add a license here, e.g. MIT, or state "This project was developed for educational purposes.")*
