#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <Arduino.h>

// Glassmorphism single-page application interface compiled into flash memory[cite: 1]
const char HTML_DASHBOARD[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ULTRAFLOAT Control Center</title>
    <style>
        body { font-family: 'Segoe UI', sans-serif; background: #0f172a; color: #f8fafc; display: flex; justify-content: center; align-items: center; min-height: 100vh; margin: 0; }
        .glass-panel { background: rgba(30, 41, 59, 0.7); backdrop-filter: blur(10px); border: 1px solid rgba(255,255,255,0.1); border-radius: 16px; padding: 2rem; width: 90%; max-width: 500px; text-align: center; box-shadow: 0 8px 32px 0 rgba(0,0,0,0.3); }
        .tank-wrapper { width: 120px; height: 200px; border: 4px solid #38bdf8; border-radius: 0 0 16px 16px; margin: 20px auto; position: relative; overflow: hidden; background: #1e293b; }
        .water-layer { position: absolute; bottom: 0; left: 0; width: 100%; background: linear-gradient(180deg, #38bdf8, #0369a1); transition: height 0.5s ease; }
        .metric-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin-top: 20px; }
        .metric-card { background: rgba(15, 23, 42, 0.5); padding: 10px; border-radius: 8px; border: 1px solid rgba(255,255,255,0.05); }
        .btn-override { background: #0284c7; color: white; border: none; padding: 12px 24px; border-radius: 8px; cursor: pointer; font-weight: bold; width: 100%; margin-top: 20px; transition: background 0.3s; }
        .btn-override:active { background: #b91c1c; }
    </style>
</head>
<body>
    <div class="glass-panel">
        <h2>ULTRAFLOAT Control Dashboard</h2>
        <div class="tank-wrapper">
            <div id="water" class="water-layer" style="height: 0%;"></div>
        </div>
        <h1 id="level-display">0%</h1>
        
        <div class="metric-grid">
            <div class="metric-card"><h3>Distance</h3><p id="dist-val">-- cm</p></div>
            <div class="metric-card"><h3>Pump Status</h3><p id="pump-val">OFF</p></div>
            <div class="metric-card"><h3>Temperature</h3><p id="temp-val">-- °C</p></div>
            <div class="metric-card"><h3>Humidity</h3><p id="hum-val">-- %</p></div>
        </div>
        <button class="btn-override" id="override-btn">HOLD MANUAL PUMP (5S)</button>
    </div>

    <script>
        let gateway = `ws://${window.location.hostname}/ws`; // WebSocket standard protocol setup[cite: 1]
        let websocket;
        
        function initWebSocket() {
            websocket = new WebSocket(gateway);
            websocket.onmessage = onMessage;
            websocket.onclose = () => { setTimeout(initWebSocket, 2000); }; // Smooth 2000ms retry logic[cite: 1]
        }

        function onMessage(event) {
            let data = JSON.parse(event.data); // Decode real-time structured JSON payload[cite: 1]
            document.getElementById('water').style.height = data.level + '%';
            document.getElementById('level-display').innerText = data.level + '%';
            document.getElementById('dist-val').innerText = data.distance + ' cm';
            document.getElementById('pump-val').innerText = data.pump ? 'ON' : 'OFF';
            document.getElementById('temp-val').innerText = data.temp + ' °C';
            document.getElementById('hum-val').innerText = data.humidity + ' %';
        }

        window.addEventListener('load', initWebSocket);
    </script>
</body>
</html>
)rawliteral";

#endif
