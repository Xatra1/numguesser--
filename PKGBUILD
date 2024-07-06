pkgname=numguesser++
pkgver=1.4
pkgrel=1
pkgdesc="A random number guessing game written in C++"
arch=('x86_64')
url="https://github.com/Xatra1/numguesser-plus-plus"
pkgdir=pkg
license=('GPL3')
makedepends=('gcc')
source=(
    "https://github.com/Xatra1/numguesser-plus-plus/archive/refs/tags/${pkgver}.tar.gz"
)
sha256sums=(
    '43d6a3b8e4c45da64f4bc7d231381f109be0d3c295f6d2102b2ef0250ac9f947'
)
package() {
    c++ -o numguesser++ src/numguesser++.cc
    install -Dm755 numguesser++ "${pkgdir}/usr/games/numguesser++"
    install -Dm755 numguesser++ "${pkgdir}/usr/games/ng++"
    gzip src/numguesser++.1
    install -Dm644 numguesser++.1.gz "${pkgdir}/usr/share/man/man1/numguesser++.1"
    install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/numguesser++/LICENSE"
}