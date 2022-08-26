with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "dwm";
  nativeBuildInputs = [ pkg-config ];
  buildInputs = [
    xorg.libX11
    xorg.libXinerama
    xorg.libXft
  ];
}
