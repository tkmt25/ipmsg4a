Add-Type -AssemblyName PresentationFramework

$xaml = [xml](Get-Content "view.xaml")
$reader = (New-Object System.Xml.XmlNodeReader $xaml)
$window = [Windows.Markup.XamlReader]::Load( $reader )

$button = $window.FindName("button")
$table = $window.FindName("table")
$text = $window.FindName("text")

$button.add_Click.Invoke({
			     $table.Items.Clear()
			     Get-EventLog Application |
			       Where-Object { $_.EntryType -eq "Error" } |
			       Where-Object { $_.Message -match $text.Text } |
			       Select-Object -First 100 | 
			       ForEach-Object {
				   $table.AddChild($_)
			       }
})

$window.ShowDialog()
