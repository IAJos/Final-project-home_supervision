const char Home[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css" integrity="sha512-DTOQO9RWCH3ppGqcWaEA1BIZOC6xxalwEsw9c2QQeAIftl+Vegovlnee1c9QX4TctnWMn13TZye+giMm8e2LwA==" crossorigin="anonymous" referrerpolicy="no-referrer" />
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
  <style type="text/css">
    .temp {
      color: #b85100;
    }

    .air {
      color: #635f98;
    }

    .light {
      color: #168665;
    }

    .item {
      border-radius: 5px;
      text-align: center;
      height: 200px;
      display: flex;
      align-items: center;
      justify-content: center;
    }

    .logo {
      margin: 4px;
    }
    
  </style>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <script type="text/javascript">
    google.charts.load('current', {'packages':['bar']});
    google.charts.setOnLoadCallback(drawChart);

    function drawChart() {
      var data = google.visualization.arrayToDataTable([
        ['Time', 'Light level', 'Temeprature', 'Air quality'],
        ['10S', 1000, 400, 200],
        ['20S', 1170, 460, 250],
        ['30S', 660, 1120, 300],
        ['40S', 1030, 540, 350],
        ['50S', 1030, 540, 350],
        ['60S', 1030, 540, 350],
        ['70S', 1030, 540, 350],
        ['80S', 1030, 540, 350],
      ]);

      var options = {
        chart: {
          title: 'Home supervision',
          subtitle: 'Data collection for this day',
        },
        bars: 'vertical',
        vAxis: {format: 'decimal'},
        height: 400,
        width: 800,
        colors: ['#1b9e77', '#d95f02', '#7570b3']
      };

      var chart = new google.charts.Bar(document.getElementById('chart_div'));

      chart.draw(data, google.charts.Bar.convertOptions(options));

      var btns = document.getElementById('btn-group');

      btns.onclick = function (e) {

        if (e.target.tagName === 'BUTTON') {
          options.vAxis.format = e.target.id === 'none' ? '' : e.target.id;
          chart.draw(data, google.charts.Bar.convertOptions(options));
        }
      }
    }  

    const eventSource = new EventSource('/events');

    eventSource.onmessage = function(event) {
      document.getElementById('temp').textContent = '' + event.data;
    }
  </script>
</head>
<body>    
  <div class="col">
    <div class="row">
      <div class="col"></div>
      <div class="col">
        <div id="chart_div"></div>
      </div>
      <div class="col"></div>
    </div>
    <div class="row">
      <div class="col"></div>
        <div class="col">
          <div class="col pb-5 pt-2">
            <div class="row">
              <div class="col card shadow m-2 light item">
                  <span class="h5">
                    <i class="fa-solid fa-sun logo"></i>
                    <u> Light level</u>
                  </span>
                  <span class="h1 mt-4">
                    <i>
                      <span id="light">55</span>
                      <span> %</span>
                    </i>
                  </span>
              </div>
              <div class="col m-2 card shadow temp item">
                  <span class="h5">
                    <i class="fa-solid fa-temperature-low logo"></i>
                    <u> Temperature</u>
                  </span>
                    <span class="h1 mt-4">
                      <i>
                        <span id="temp"></span>
                        <span> °C</span>
                      </i>
                    </span>
              </div>
              <div class="col card shadow m-2 air item">
                  <span class="h5">
                    <i class="fa-solid fa-wind logo"></i>
                    <u> Air Quality</u>
                  </span>
                  <span class="h1 mt-4">
                    <i>
                      <span id="air">55</span>
                      <span> ppm</span>
                    </i>
                  </span>
              </div>
            </div>
            <div class="row">
              <div class="col card shadow m-2 Notation item" id="btn-group">
                <div class="row">
                  <span class="h5 mb-3">
                    <strong>
                      <u>CHART NOTATION FORMAT</u>
                    </strong>
                  </span>
                </div>
                <div class="row m-2">
                  <div class="col">
                    <button class="btn btn-outline-secondary" id="none">Format</button></div>
                  <div class="col">
                    <button class="btn btn-outline-info" id="scientific">Scientific</button></div>
                </div>
                <div class="row m-2 ">
                  <div class="col">
                    <button class="btn btn-outline-primary" id="decimal">Decimal</button></div>
                  <div class="col">
                    <button class="btn btn-outline-success" id="short">Short</button></div>
                </div>
              </div>
              <div class="col card shadow m-2 item">
                <div class="row">
                  <span class="h5">
                    <i class="fa-solid fa-plug logo"></i>
                    <strong>
                      <u>ACTIONS</u>
                    </strong>
                  </span>
                </div>
                <div class="row mt-3">
                  <div class="col">
                    <span class="h7">
                      <i class="fa-solid fa-lightbulb led-txt" id="led"></i> LIGHT
                    </span>
                    <br>
                    <span>
                      <a href="/led/on" class="btn btn-success badge">On</a>
                      <a href="/led/off" class="btn btn-danger badge">Off</a>
                    </span>
                  </div>
                  <div class="col">
                    <span class="h7">
                      <i class="fa-solid fa-fan"></i> FAN
                    </span>
                    <br>
                    <span>
                      <a href="/fan/on" class="btn btn-success badge">On</a>
                      <a href="/fan/off" class="btn btn-danger badge">Off</a>
                    </span>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div class="col"></div>
      </div>
    </div>
  </div>
</body>
</html>
)=====";
