<!DOCTYPE html>
<html lang="en">
    <head>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    
        <!-- Bootstrap CSS v5.2.1 -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-iYQeCzEYFbKjA/T2uDLTpkwGzCiq6soy8tYaI1GyVh/UjpbCx/TYkiZhlZB6+fzT" crossorigin="anonymous">
    
        <link rel="stylesheet" href="css/style.css">
    </head>

    <?php
    include_once 'config.php';
    $sql = mysqli_query($koneksi, "SELECT * from DTsensor ORDER BY time DESC LIMIT 1");
    $row = mysqli_fetch_array($sql);
    $data_suhu = $row["suhu"];
    ?>
    
    <body>
        <div id="myProgress">
            <div id="myBar">10%</div>
        </div>
    </body>
    
    <script src="jquery/jquery.min.js"></script>
    
    <script>
        $(document).ready(function () {
                var elem = document.getElementById("myBar");
                var width = 0;
                var id = setInterval(frame,1);
                
                function frame() {
                    width = <?php echo $data_suhu; ?>;
                    
                    if (width < 10) {
                            elem.style.backgroundColor = "#FF4E33";
                            elem.style.width = width + "%";
                            elem.innerHTML = width + "cm";
                        }
                        if (width > 10 && width <= 20) {
                            elem.style.backgroundColor = "#FFDA33";
                            elem.style.width = width + "%";
                            elem.innerHTML = width + "cm";
                        }
                        if (width > 20 && width <= 100) {
                            elem.style.width = width + "%";
                            elem.innerHTML = width + "cm";
                        }
                        if (width > 100) {
                            elem.style.width = "100%";
                            elem.innerHTML = width + "cm";
                        }
                }
            })
    </script>
</html>
