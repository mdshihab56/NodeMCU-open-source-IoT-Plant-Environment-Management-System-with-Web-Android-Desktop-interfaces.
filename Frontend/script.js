function auth() {
  let u = document.getElementById("user").value;
  let p = document.getElementById("pass").value;

  fetch(`/login?u=${u}&p=${p}`)
    .then((res) => res.text())
    .then((txt) => {
      if (txt === "OK") {
        document.getElementById("login").style.display = "none";
        document.getElementById("panel").style.display = "block";
      } else {
        alert("Unauthorized credentials!");
      }
    });
}

function toggle(id, state) {
  fetch(`/relay?id=${id}&state=${state}`)
    .then((res) => res.text())
    .then((status) => console.log(`Switch ${id} is now ${status}`));
}

function toggleMode() {
  if (document.body.classList.contains("dark-mode")) {
    document.body.classList.remove("dark-mode");
    document.body.classList.add("light-mode");
    localStorage.setItem("theme", "light");
  } else {
    document.body.classList.remove("light-mode");
    document.body.classList.add("dark-mode");
    localStorage.setItem("theme", "dark");
  }
}

window.onload = () => {
  const savedTheme = localStorage.getItem("theme") || "dark";
  document.body.classList.add(savedTheme);
};
