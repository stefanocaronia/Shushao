# Function to get values from premake5.lua
function Get-ValueFromPremakeFile($key) {
    $premakeFilePath = "./premake5.lua"
    $pattern = "$key\s*=\s*([^""\s]*)|""([^""]*)"""
    $content = Get-Content $premakeFilePath -Raw
    if ($content -match "$key\s*=\s*(?:'([^']*)'|""([^""]*)""|(\S*))") {
        $value = if ($null -ne $matches[3]) { $matches[3] } elseif ($null -ne $matches[2]) { $matches[2] } else { $matches[1] }
        # Write-Host "Value for $key is $value"
        return $value
    }

    Write-Error "Value for $key is null!"
    return $null
}

# Read premake5.lua to get vcpkg information
$vcpkgRoot = Get-ValueFromPremakeFile "vcpkg_root"
$vcpkgTriplet = Get-ValueFromPremakeFile "vcpkg_triplet"
$vcpkgManifest = Get-ValueFromPremakeFile "vcpkg_manifest"
$vcpkgUseStatic = Get-ValueFromPremakeFile "vcpkg_use_static_libraries"
$vcpkgInstalledPackagesDir = Get-ValueFromPremakeFile "vcpkg_installed_packages"

# Write-Output "End!"
# return 0;

# Convert the string to a boolean
$vcpkgUseStatic = $vcpkgUseStatic.ToLower()
if ($vcpkgUseStatic -eq 'true') {
    $vcpkgUseStatic = $true
} else {
    $vcpkgUseStatic = $false
}

# Get the project files
$projectFiles = Get-ChildItem -Recurse -Filter *.vcxproj

# Function to set the XML element
function Set-XmlElement($elementName, $elementValue, $propertyGroup, $ns) {
    $element = $propertyGroup.SelectSingleNode("./ns:$elementName", $ns)
    if ($null -eq $element) {
        $element = $doc.CreateElement($elementName, $ns.LookupNamespace('ns'))
        $propertyGroup.AppendChild($element)
    }
    $element.InnerText = $elementValue
}

foreach ($projectFile in $projectFiles) {
    # Load the XML document
    $doc = [xml](Get-Content $projectFile.FullName)

    # Define the XML namespaces used in the vcxproj file
    $ns = New-Object 'System.Xml.XmlNamespaceManager' $doc.NameTable
    $ns.AddNamespace('ns', 'http://schemas.microsoft.com/developer/msbuild/2003')

    # Get or create the PropertyGroup that contains the Vcpkg configuration
    $propertyGroup = $doc.SelectSingleNode("/ns:Project/ns:PropertyGroup[@Label='Globals']", $ns)
    if ($null -eq $propertyGroup) {
        $propertyGroup = $doc.CreateElement("PropertyGroup", $ns.LookupNamespace('ns'))
        $propertyGroup.SetAttribute('Label', 'Globals')
        $doc.DocumentElement.AppendChild($propertyGroup)
    }

    # Create or set the Vcpkg configuration nodes
    Set-XmlElement "VcpkgTriplet" $vcpkgTriplet $propertyGroup $ns
    Set-XmlElement "VcpkgEnabled" 'true' $propertyGroup $ns
    Set-XmlElement "VcpkgEnableManifest" 'true' $propertyGroup $ns
    Set-XmlElement "VcpkgManifestInstall" 'true' $propertyGroup $ns
    Set-XmlElement "VcpkgInstalledDir" "${vcpkgRoot}/${vcpkgInstalledPackagesDir}/${vcpkgTriplet}" $propertyGroup $ns
    Set-XmlElement "VcpkgUseStatic" $vcpkgUseStatic $propertyGroup $ns

    # Save the changes
    $doc.Save($projectFile.FullName)
}

Write-Output "Vcpkg configuration updated in project files"


# foreach ($projectFile in $projectFiles) {
#     # Load the XML document
#     $doc = [xml](Get-Content $projectFile.FullName)

#     # Define the XML namespaces used in the vcxproj file
#     $ns = New-Object 'System.Xml.XmlNamespaceManager' $doc.NameTable
#     $ns.AddNamespace('ns', 'http://schemas.microsoft.com/developer/msbuild/2003')

#     # Get or create the PropertyGroup that contains the Vcpkg configuration
#     $propertyGroup = $doc.SelectSingleNode("/ns:Project/ns:PropertyGroup[@Label='Globals']", $ns)
#     if ($null -eq $propertyGroup) {
#         $propertyGroup = $doc.CreateElement("PropertyGroup", $ns.LookupNamespace('ns'))
#         $propertyGroup.SetAttribute('Label', 'Globals')
#         $doc.DocumentElement.AppendChild($propertyGroup)
#     }

#     # Create or set the Vcpkg configuration nodes
#     $vcpkgTripletElement = $doc.CreateElement("VcpkgTriplet", $ns.LookupNamespace('ns'))
#     $vcpkgTripletElement.InnerText = $vcpkgTriplet
#     $propertyGroup.AppendChild($vcpkgTripletElement)

#     $vcpkgEnabledElement = $doc.CreateElement("VcpkgEnabled", $ns.LookupNamespace('ns'))
#     $vcpkgEnabledElement.InnerText = 'true'
#     $propertyGroup.AppendChild($vcpkgEnabledElement)

#     $vcpkgEnableManifestElement = $doc.CreateElement("VcpkgEnableManifest", $ns.LookupNamespace('ns'))
#     $vcpkgEnableManifestElement.InnerText = 'true'
#     $propertyGroup.AppendChild($vcpkgEnableManifestElement)

#     $vcpkgManifestInstallElement = $doc.CreateElement("VcpkgManifestInstall", $ns.LookupNamespace('ns'))
#     $vcpkgManifestInstallElement.InnerText = 'true'
#     $propertyGroup.AppendChild($vcpkgManifestInstallElement)

#     $vcpkgInstalledDirElement = $doc.CreateElement("VcpkgInstalledDir", $ns.LookupNamespace('ns'))
#     $vcpkgInstalledDirElement.InnerText = "${vcpkgRoot}/installed/${vcpkgTriplet}"
#     $propertyGroup.AppendChild($vcpkgInstalledDirElement)

#     # Save the changes
#     $doc.Save($projectFile.FullName)
# }

# Write-Output "Vcpkg configuration updated in project files"
