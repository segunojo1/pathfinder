```markdown
# 🧠 C++ + HTML CGI Quiz App (Using XAMPP Apache)

This project integrates **C++ CGI** with **HTML/CSS** to create a dynamic quiz web application running on **XAMPP's Apache server**.

---

## 📁 Project Structure

```

/cgi-bin/
├── quiz.cpp       # C++ source file (CGI logic)
├── quiz.exe       # Compiled executable
└── quiz.cgi       # (Optional) alias or copy of quiz.exe

/public\_html/
├── index.html     # Frontend interface
└── style.css      # Page styling

````

---

## 🧰 Prerequisites

- [XAMPP](https://www.apachefriends.org/index.html) (Apache module)
- A working C++ compiler (e.g., `g++`)
- Windows OS

---

## ⚙️ Setup Instructions

### 1. 🚀 Install & Start XAMPP

- Install XAMPP and open the **XAMPP Control Panel**
- Start the **Apache** module

### 2. 🧱 Compile the C++ File

Navigate to your project directory and compile `quiz.cpp`:

```bash
g++ quiz.cpp -o "C:/xampp/cgi-bin/quiz.exe"
````

> 💡 You can rename `quiz.exe` to `quiz.cgi` or keep both if needed.

### 3. 📄 Place Files Correctly

* Put your **compiled `quiz.exe` or `quiz.cgi`** in:
  `C:/xampp/cgi-bin/`
* Put your **frontend files** in:
  `C:/xampp/htdocs/public_html/`

> Apache serves HTML/CSS/JS from `htdocs`, and executes CGI from `cgi-bin`.

### 4. 🛠️ Configure Apache for CGI (if not already)

1. Open:
   `C:/xampp/apache/conf/httpd.conf`
2. Ensure these lines are uncommented:

```apache
ScriptAlias /cgi-bin/ "C:/xampp/cgi-bin/"
<Directory "C:/xampp/cgi-bin">
    AllowOverride None
    Options +ExecCGI
    AddHandler cgi-script .cgi .exe
    Require all granted
</Directory>
```

3. Save and restart Apache in the XAMPP Control Panel.

---

## 🌐 How to Run

1. Open your browser.
2. Navigate to:
   `http://localhost/public_html/index.html`
3. Your HTML page will interact with the CGI executable located at:
   `http://localhost/cgi-bin/quiz.cgi` or `quiz.exe`

---

## 📌 Example Integration (HTML)

```html
<form action="/cgi-bin/quiz.cgi" method="GET">
  <input type="submit" value="Start Quiz">
</form>
```

Or using an `<iframe>`:

```html
<iframe src="/cgi-bin/quiz.cgi" width="100%" height="300"></iframe>
```

---

## ❗ Troubleshooting

* **500 Internal Server Error**

  * Make sure your CGI starts with:
    `std::cout << "Content-type: text/html\n\n";`
  * Ensure the file has execution permissions

* **Output is blank or malformed?**

  * Ensure your C++ outputs valid HTML + headers

* **Page not found?**

  * Confirm correct paths:
    `htdocs/public_html/index.html`
    `cgi-bin/quiz.cgi`

---

## 📌 Notes

* You can test your CGI directly at:
  `http://localhost/cgi-bin/quiz.cgi`
* Use `quiz.cgi` as an alias if you want clean naming (copy `quiz.exe` and rename)

---

## 👨‍💻 Author

Segun Ojo – 2025
Built with ❤️ using C++, HTML, and Apache CGI

```

