<!doctype html>
<html lang="en">

<head>
    <title>Monitoring suhu dan pH air</title>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS v5.2.1 -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-iYQeCzEYFbKjA/T2uDLTpkwGzCiq6soy8tYaI1GyVh/UjpbCx/TYkiZhlZB6+fzT" crossorigin="anonymous">

    <link rel="stylesheet" href="css/style.css">

    <?php
    include_once "config.php";

    $sql1 = mysqli_query($koneksi, "SELECT * from DTsensor ORDER BY time DESC LIMIT 1");
    $row = mysqli_fetch_array($sql1);
    ?>
</head>

<body>
    <header>
        <!-- place navbar here -->
    </header>
    <main>
        <nav class="navbar navbar-dark bg-primary">
            <a class="navbar-brand" style="margin-left:2vw;" href="index.php">Monitoring suhu dan pH air</a>
            <button class="navbar-toggler d-lg-none" type="button" data-bs-toggle="collapse" data-bs-target="#collapsibleNavId" aria-controls="collapsibleNavId" aria-expanded="false" aria-label="Toggle navigation"></button>
            <div class="collapse navbar-collapse" id="collapsibleNavId">
                <ul class="navbar-nav mt-2 mt-lg-0">
                    <li class="nav-item">
                        <a class="nav-link" href="halaman_history.php">History</a>
                    </li>
            </div>
        </nav>

        <div class="container">
            <div class="col">
                <h1 class="text-center judul">Halaman Monitoring suhu dan pH air</h1>
            </div>
        </div>
        <div class="container">
            <div class="col-7 mx-auto">
                <!-- <div id="dataBar"> -->
                <!--<div id="myBar"></div>-->
                <!-- </div> -->
                <br>
                <div class="row">
                    <div class="col-6">
                        <h2 class="text-center">Status suhu : <span><?php echo $row["suhu"]; ?></span></h2>
                    </div>

                    <div class="col-6">
                        <h2 class="text-center">Status pH : <span><?php echo $row["ph"]; ?></span></h2>
                    </div>
                </div>
                <br>
                <br>
            </div>
        </div>
        <div class="container-fluid" style="text-align: -webkit-center;">
            <div class="col-7" style="text-align: center;">
                <h3>Data Suhu dan pH</h3>
                <div class="table-responsive">
                    <table class="table table-primary">
                        <thead>
                            <tr>
                                <th scope="col">no</th>
                                <th scope="col">ketinggian</th>
                                <th scope="col">Status</th>
                                <th scope="col">Waktu</th>
                            </tr>
                        </thead>
                        <tbody id="data">
                        </tbody>
                    </table>
                </div>

            </div>
        </div>

    </main>
    <footer>
        <!-- place footer here -->
    </footer>
    <!-- Bootstrap JavaScript Libraries -->
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.6/dist/umd/popper.min.js" integrity="sha384-oBqDVmMz9ATKxIep9tiCxS/Z9fNfEXiDAYTujMAeBAsjFuCZSmKbSSUnQlmh/jp3" crossorigin="anonymous">
    </script>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.min.js" integrity="sha384-7VPbUDkoPSGFnVtYi0QogXtr74QeVeeIs99Qfg5YCF+TidwNdjvaKZX19NZ/e6oz" crossorigin="anonymous">
    </script>

    <script src="jquery/jquery.min.js"></script>

    <script>
        $(document).ready(function() {
            setInterval(function() {
                $("#data").load("datahistory.php");
                $('#dataBar').load("data_progress_bar.php")
            }, 1000);
        })
    </script>
</body>

</html>