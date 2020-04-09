param(
    $fromPath = "C:\Users\ProtoLAB\Documents\Coronavirus Response\apollobvm\ApolloBVM",
    $toPath = "C:\Users\ProtoLAB\Documents\Arduino\libraries"
)

Copy-Item -Path $fromPath -Destination $toPath -Recurse -Force
