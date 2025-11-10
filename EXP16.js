<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Dynamic List & Carousel</title>
  <style>
    body { font-family: sans-serif; margin: 2rem; }
    #list { margin: 1rem 0; }
    .item { padding: 0.5rem; border-bottom: 1px solid #ddd; }
    #carousel { position: relative; width: 400px; height: 250px; overflow: hidden; margin: 2rem 0; }
    .slides { display: flex; transition: transform 0.3s ease; width: 100%; height: 100%; }
    .slide { min-width: 100%; height: 100%; }
    .slide img { width: 100%; height: 100%; object-fit: cover; }
    button.nav { position: absolute; top: 50%; transform: translateY(-50%); background: rgba(0,0,0,0.5); color: #fff; border: none; padding: 0.5rem; cursor: pointer; }
    button.prev { left: 10px; }
    button.next { right: 10px; }
    .controls { margin: 1rem 0; }
  </style>
</head>
<body>

  <!-- Dynamic List -->
  <h2>Dynamic List</h2>
  <input type="text" id="input" placeholder="Enter item" />
  <button id="addBtn">Add Item</button>
  <ul id="list"></ul>

  <!-- Image Carousel -->
  <h2>Image Carousel</h2>
  <div id="carousel">
    <div class="slides"></div>
    <button class="nav prev">❮</button>
    <button class="nav next">❯</button>
  </div>
  <div class="controls">
    <button id="playPause">Pause</button>
    <span>Autoplay: <span id="status">On</span></span>
  </div>

  <script>
    // === Dynamic List ===
    const list = document.querySelector('#list');
    const input = document.querySelector('#input');
    const addBtn = document.querySelector('#addBtn');

    addBtn.addEventListener('click', () => {
      if (!input.value.trim()) return;
      const li = document.createElement('li');
      li.className = 'item';
      li.textContent = input.value;
      list.appendChild(li);
      input.value = '';
    });

    // Allow Enter key
    input.addEventListener('keypress', e => e.key === 'Enter' && addBtn.click());

    // === Carousel ===
    const slidesContainer = document.querySelector('.slides');
    const images = [
      'https://picsum.photos/400/250?random=1',
      'https://picsum.photos/400/250?random=2',
      'https://picsum.photos/400/250?random=3'
    ];

    let current = 0;
    let autoplay = true;
    let interval;

    // Create slides
    images.forEach(src => {
      const div = document.createElement('div');
      div.className = 'slide';
      const img = document.createElement('img');
      img.src = src;
      img.alt = 'Carousel image';
      div.appendChild(img);
      slidesContainer.appendChild(div);
    });

    const slides = document.querySelectorAll('.slide');
    const total = slides.length;

    function showSlide(n) {
      current = (n + total) % total;
      slidesContainer.style.transform = `translateX(-${current * 100}%)`;
    }

    // Navigation buttons
    document.querySelector('.prev').onclick = () => showSlide(current - 1);
    document.querySelector('.next').onclick = () => showSlide(current + 1);

    // Arrow keys
    document.addEventListener('keydown', e => {
      if (e.key === 'ArrowLeft') showSlide(current - 1);
      if (e.key === 'ArrowRight') showSlide(current + 1);
    });

    // Touch swipe
    let touchStartX = 0;
    document.getElementById('carousel').addEventListener('touchstart', e => {
      touchStartX = e.touches[0].clientX;
    });
    document.getElementById('carousel').addEventListener('touchend', e => {
      const diff = touchStartX - e.changedTouches[0].clientX;
      if (Math.abs(diff) > 50) showSlide(current + (diff > 0 ? 1 : -1));
    });

    // Autoplay
    function startAutoplay() {
      interval = setInterval(() => showSlide(current + 1), 3000);
    }
    function stopAutoplay() {
      clearInterval(interval);
    }

    const playPauseBtn = document.getElementById('playPause');
    const status = document.getElementById('status');
    playPauseBtn.onclick = () => {
      if (autoplay) {
        stopAutoplay();
        playPauseBtn.textContent = 'Play';
        status.textContent = 'Off';
      } else {
        startAutoplay();
        playPauseBtn.textContent = 'Pause';
        status.textContent = 'On';
      }
      autoplay = !autoplay;
    };

    // Initialize
    showSlide(0);
    startAutoplay();
  </script>
</body>
</html>
