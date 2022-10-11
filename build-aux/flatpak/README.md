# Flatpak Build Instructions

## Prerequisites
To build the Flatpak, install the `flatpak` and `flatpak-builder` packages
from your repositories. Then, [add Flathub](https://flatpak.org/setup/).

Now, install the KDE SDK:
```sh
flatpak install flathub org.kde.Sdk//5.15-22.08
```

## Building and installing
To build and install the app locally:

```sh
flatpak-builder --force-clean --install --user builddir build-aux/flatpak/org.thentrythis.Samplebrain.yaml
```

## Building and exporting
To build and export a Flatpak bundle:

```sh
flatpak-builder --force-clean --repo=repo builddir build-aux/flatpak/org.thentrythis.Samplebrain.yaml
flatpak build-bundle repo org.thentrythis.Samplebrain.flatpak org.thentrythis.Samplebrain
```

To install the bundle:

```sh
flatpak install org.thentrythis.Samplebrain.flatpak
```