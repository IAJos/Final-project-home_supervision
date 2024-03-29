google.charts.load('current', {'packages':['bar']});
    google.charts.setOnLoadCallback(drawChart);

    var fullData = [
      ['Time', 'Light level', 'Temeprature', 'Air quality'],
      ['10S', 0, 0, 0],
      ['20S', 0, 0, 0],
      ['30S', 0, 0, 0],
      ['40S', 0, 0, 0],
      ['50S', 0, 0, 0],
      ['60S', 0, 0, 0],
      ['70S', 0, 0, 0],
      ['80S', 0, 0, 0],
    ];

    function drawChart() {
      var data = google.visualization.arrayToDataTable(fullData);

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

    function getLightValue() {
      fetch("/readLight")
        .then(response => response.text())
        .then(data => {
          document.getElementById("llevel").innerText = data;
        });
    }

    function getTemperatureValue() {
      fetch("/readtemperature")
        .then(response => response.text())
        .then(data => {
          document.getElementById("tmp").innerText = data;
        });
    }

    function getGazValue() {
      fetch("/readGaz")
        .then(response => response.text())
        .then(data => {
          document.getElementById("gaz").innerText = data;
        });
    }
 
    function getData() {
      fetch("/data")
        .then(response => response.json())
        .then(data => {

          for (var i = 0; i < data.length; i++) {
            var index_data = ((i+1)*10) + "S";

            for (var j = 0; j < fullData.length; j++) {
              var index_fullData = fullData[j][0];

              if(index_data == index_fullData){
                fullData[j][1] = data[i].light;
                fullData[j][2] = data[i].temperature;
                fullData[j][3] = data[i].gaz;
              }
            }
          }
        });
    }

    getData();
    getLightValue();
    getTemperatureValue();
    getGazValue();