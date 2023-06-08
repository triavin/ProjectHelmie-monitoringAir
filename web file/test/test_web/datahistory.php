<?php
include_once 'config.php';
$no = 1;
$sql = mysqli_query($koneksi, "SELECT * from DTsensor ORDER BY time DESC LIMIT 10");
while ($row1 = mysqli_fetch_array($sql)) {
?>
    
    <tr>
        <th scope="row">
            <?php echo $no++; ?>
        </th>
        <td>
            <?php echo $row1['suhu']; ?>
        </td>
        <td>
            <?php echo $row1['ph']; ?>
        </td>
        <td>
            <?php echo $row1['time']; ?>
        </td>
    </tr>
<?php
}
?>