


$COM = [System.IO.Ports.SerialPort]::getportnames()
$port= new-Object System.IO.Ports.SerialPort $COM,115200,None,8,one

function Read-Com {
    
    $port.Open()
    $port.ReadTimeout = 500

    do {
        try {
            $Continue = $false
            $line = $port.ReadLine()
            if($line -match "STACK") {
                Write-Output "Found STACK at: $(Get-Date -Format HH:mm:ss.ff)" >> err.log 
            }
            Write-Output "$(Get-Date -Format HH:mm:ss.ff): $line"
            $Continue = $true
        }
        catch [TimeoutException] {
            $Continue = $true
        }
        finally {
            if ($Continue -eq $false) {
                echo "Closing port" >> file.txt
                $port.Close()
                echo "Port closed" >> file.txt
            }
        }
        
    }
    while ($port.IsOpen)
    
}