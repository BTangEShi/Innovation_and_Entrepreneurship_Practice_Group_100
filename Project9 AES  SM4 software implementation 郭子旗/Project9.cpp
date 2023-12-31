#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <chrono>
#include <string.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdint>
#include <immintrin.h>
#include <iostream>




static const uint32_t TboxTable3[256] = {
    0xd55b5b8e,0x924242d0,0xeaa7a74d,0xfdfbfb06,0xcf3333fc,0xe2878765,0x3df4f4c9,0xb5dede6b,0x1658584e,0xb4dada6e,0x14505044,0xc10b0bca,0x28a0a088,0xf8efef17,0x2cb0b09c,0x5141411,
0x2bacac87,0x669d9dfb,0x986a6af2,0x77d9d9ae,0x2aa8a882,0xbcfafa46,0x4101014,0xc00f0fcf,0xa8aaaa02,0x45111154,0x134c4c5f,0x269898be,0x4825256d,0x841a1a9e,0x618181e,0x9b6666fd,
0x9e7272ec,0x4309094a,0x51414110,0xf7d3d324,0x934646d5,0xecbfbf53,0x9a6262f8,0x7be9e992,0x33ccccff,0x55515104,0xb2c2c27,0x420d0d4f,0xeeb7b759,0xcc3f3ff3,0xaeb2b21c,0x638989ea,
0xe7939374,0xb1cece7f,0x1c70706c,0xaba6a60d,0xca2727ed,0x8202028,0xeba3a348,0x975656c1,0x82020280,0xdc7f7fa3,0x965252c4,0xf9ebeb12,0x74d5d5a1,0x8d3e3eb3,0x3ffcfcc3,0xa49a9a3e,
0x461d1d5b,0x71c1c1b,0xa59e9e3b,0xfff3f30c,0xf0cfcf3f,0x72cdcdbf,0x175c5c4b,0xb8eaea52,0x810e0e8f,0x5865653d,0x3cf0f0cc,0x1964647d,0xe59b9b7e,0x87161691,0x4e3d3d73,0xaaa2a208,
0x69a1a1c8,0x6aadadc7,0x83060685,0xb0caca7a,0x70c5c5b5,0x659191f4,0xd96b6bb2,0x892e2ea7,0xfbe3e318,0xe8afaf47,0xf3c3c33,0x4a2d2d67,0x71c1c1b0,0x5759590e,0x9f7676e9,0x35d4d4e1,
0x1e787866,0x249090b4,0xe383836,0x5f797926,0x628d8def,0x59616138,0xd2474795,0xa08a8a2a,0x259494b1,0x228888aa,0x7df1f18c,0x3bececd7,0x1040405,0x218484a5,0x79e1e198,0x851e1e9b,
0xd7535384,0x0,0x4719195e,0x565d5d0b,0x9d7e7ee3,0xd04f4f9f,0x279c9cbb,0x5349491a,0x4d31317c,0x36d8d8ee,0x208080a,0xe49f9f7b,0xa2828220,0xc71313d4,0xcb2323e8,0x9c7a7ae6,
0xe9abab42,0xbdfefe43,0x882a2aa2,0xd14b4b9a,0x41010140,0xc41f1fdb,0x38e0e0d8,0xb7d6d661,0xa18e8e2f,0xf4dfdf2b,0xf1cbcb3a,0xcd3b3bf6,0xfae7e71d,0x608585e5,0x15545441,0xa3868625,
0xe3838360,0xacbaba16,0x5c757529,0xa6929234,0x996e6ef7,0x34d0d0e4,0x1a686872,0x54555501,0xafb6b619,0x914e4edf,0x32c8c8fa,0x30c0c0f0,0xf6d7d721,0x8e3232bc,0xb3c6c675,0xe08f8f6f,
0x1d747469,0xf5dbdb2e,0xe18b8b6a,0x2eb8b896,0x800a0a8a,0x679999fe,0xc92b2be2,0x618181e0,0xc30303c0,0x29a4a48d,0x238c8caf,0xa9aeae07,0xd343439,0x524d4d1f,0x4f393976,0x6ebdbdd3,
0xd6575781,0xd86f6fb7,0x37dcdceb,0x44151551,0xdd7b7ba6,0xfef7f709,0x8c3a3ab6,0x2fbcbc93,0x30c0c0f,0xfcffff03,0x6ba9a9c2,0x73c9c9ba,0x6cb5b5d9,0x6db1b1dc,0x5a6d6d37,0x50454515,
0x8f3636b9,0x1b6c6c77,0xadbebe13,0x904a4ada,0xb9eeee57,0xde7777a9,0xbef2f24c,0x7efdfd83,0x11444455,0xda6767bd,0x5d71712c,0x40050545,0x1f7c7c63,0x10404050,0x5b696932,0xdb6363b8,
0xa282822,0xc20707c5,0x31c4c4f5,0x8a2222a8,0xa7969631,0xce3737f9,0x7aeded97,0xbff6f649,0x2db4b499,0x75d1d1a4,0xd3434390,0x1248485a,0xbae2e258,0xe6979771,0xb6d2d264,0xb2c2c270,
0x8b2626ad,0x68a5a5cd,0x955e5ecb,0x4b292962,0xc30303c,0x945a5ace,0x76ddddab,0x7ff9f986,0x649595f1,0xbbe6e65d,0xf2c7c735,0x924242d,0xc61717d1,0x6fb9b9d6,0xc51b1bde,0x86121294,
0x18606078,0xf3c3c330,0x7cf5f589,0xefb3b35c,0x3ae8e8d2,0xdf7373ac,0x4c353579,0x208080a0,0x78e5e59d,0xedbbbb56,0x5e7d7d23,0x3ef8f8c6,0xd45f5f8b,0xc82f2fe7,0x39e4e4dd,0x49212168
};
static const uint32_t TboxTable2[256] = {
    0x5b5b8ed5,0x4242d092,0xa7a74dea,0xfbfb06fd,0x3333fccf,0x878765e2,0xf4f4c93d,0xdede6bb5,0x58584e16,0xdada6eb4,0x50504414,0xb0bcac1,0xa0a08828,0xefef17f8,0xb0b09c2c,0x14141105,
0xacac872b,0x9d9dfb66,0x6a6af298,0xd9d9ae77,0xa8a8822a,0xfafa46bc,0x10101404,0xf0fcfc0,0xaaaa02a8,0x11115445,0x4c4c5f13,0x9898be26,0x25256d48,0x1a1a9e84,0x18181e06,0x6666fd9b,
0x7272ec9e,0x9094a43,0x41411051,0xd3d324f7,0x4646d593,0xbfbf53ec,0x6262f89a,0xe9e9927b,0xccccff33,0x51510455,0x2c2c270b,0xd0d4f42,0xb7b759ee,0x3f3ff3cc,0xb2b21cae,0x8989ea63,
0x939374e7,0xcece7fb1,0x70706c1c,0xa6a60dab,0x2727edca,0x20202808,0xa3a348eb,0x5656c197,0x2028082,0x7f7fa3dc,0x5252c496,0xebeb12f9,0xd5d5a174,0x3e3eb38d,0xfcfcc33f,0x9a9a3ea4,
0x1d1d5b46,0x1c1c1b07,0x9e9e3ba5,0xf3f30cff,0xcfcf3ff0,0xcdcdbf72,0x5c5c4b17,0xeaea52b8,0xe0e8f81,0x65653d58,0xf0f0cc3c,0x64647d19,0x9b9b7ee5,0x16169187,0x3d3d734e,0xa2a208aa,
0xa1a1c869,0xadadc76a,0x6068583,0xcaca7ab0,0xc5c5b570,0x9191f465,0x6b6bb2d9,0x2e2ea789,0xe3e318fb,0xafaf47e8,0x3c3c330f,0x2d2d674a,0xc1c1b071,0x59590e57,0x7676e99f,0xd4d4e135,
0x7878661e,0x9090b424,0x3838360e,0x7979265f,0x8d8def62,0x61613859,0x474795d2,0x8a8a2aa0,0x9494b125,0x8888aa22,0xf1f18c7d,0xececd73b,0x4040501,0x8484a521,0xe1e19879,0x1e1e9b85,
0x535384d7,0x0,0x19195e47,0x5d5d0b56,0x7e7ee39d,0x4f4f9fd0,0x9c9cbb27,0x49491a53,0x31317c4d,0xd8d8ee36,0x8080a02,0x9f9f7be4,0x828220a2,0x1313d4c7,0x2323e8cb,0x7a7ae69c,
0xabab42e9,0xfefe43bd,0x2a2aa288,0x4b4b9ad1,0x1014041,0x1f1fdbc4,0xe0e0d838,0xd6d661b7,0x8e8e2fa1,0xdfdf2bf4,0xcbcb3af1,0x3b3bf6cd,0xe7e71dfa,0x8585e560,0x54544115,0x868625a3,
0x838360e3,0xbaba16ac,0x7575295c,0x929234a6,0x6e6ef799,0xd0d0e434,0x6868721a,0x55550154,0xb6b619af,0x4e4edf91,0xc8c8fa32,0xc0c0f030,0xd7d721f6,0x3232bc8e,0xc6c675b3,0x8f8f6fe0,
0x7474691d,0xdbdb2ef5,0x8b8b6ae1,0xb8b8962e,0xa0a8a80,0x9999fe67,0x2b2be2c9,0x8181e061,0x303c0c3,0xa4a48d29,0x8c8caf23,0xaeae07a9,0x3434390d,0x4d4d1f52,0x3939764f,0xbdbdd36e,
0x575781d6,0x6f6fb7d8,0xdcdceb37,0x15155144,0x7b7ba6dd,0xf7f709fe,0x3a3ab68c,0xbcbc932f,0xc0c0f03,0xffff03fc,0xa9a9c26b,0xc9c9ba73,0xb5b5d96c,0xb1b1dc6d,0x6d6d375a,0x45451550,
0x3636b98f,0x6c6c771b,0xbebe13ad,0x4a4ada90,0xeeee57b9,0x7777a9de,0xf2f24cbe,0xfdfd837e,0x44445511,0x6767bdda,0x71712c5d,0x5054540,0x7c7c631f,0x40405010,0x6969325b,0x6363b8db,
0x2828220a,0x707c5c2,0xc4c4f531,0x2222a88a,0x969631a7,0x3737f9ce,0xeded977a,0xf6f649bf,0xb4b4992d,0xd1d1a475,0x434390d3,0x48485a12,0xe2e258ba,0x979771e6,0xd2d264b6,0xc2c270b2,
0x2626ad8b,0xa5a5cd68,0x5e5ecb95,0x2929624b,0x30303c0c,0x5a5ace94,0xddddab76,0xf9f9867f,0x9595f164,0xe6e65dbb,0xc7c735f2,0x24242d09,0x1717d1c6,0xb9b9d66f,0x1b1bdec5,0x12129486,
0x60607818,0xc3c330f3,0xf5f5897c,0xb3b35cef,0xe8e8d23a,0x7373acdf,0x3535794c,0x8080a020,0xe5e59d78,0xbbbb56ed,0x7d7d235e,0xf8f8c63e,0x5f5f8bd4,0x2f2fe7c8,0xe4e4dd39,0x21216849
};
static const uint32_t TboxTable1[256] = {
0x5b8ed55b,0x42d09242,0xa74deaa7,0xfb06fdfb,0x33fccf33,0x8765e287,0xf4c93df4,0xde6bb5de,0x584e1658,0xda6eb4da,0x50441450,0xbcac10b,0xa08828a0,0xef17f8ef,0xb09c2cb0,0x14110514,
0xac872bac,0x9dfb669d,0x6af2986a,0xd9ae77d9,0xa8822aa8,0xfa46bcfa,0x10140410,0xfcfc00f,0xaa02a8aa,0x11544511,0x4c5f134c,0x98be2698,0x256d4825,0x1a9e841a,0x181e0618,0x66fd9b66,
0x72ec9e72,0x94a4309,0x41105141,0xd324f7d3,0x46d59346,0xbf53ecbf,0x62f89a62,0xe9927be9,0xccff33cc,0x51045551,0x2c270b2c,0xd4f420d,0xb759eeb7,0x3ff3cc3f,0xb21caeb2,0x89ea6389,
0x9374e793,0xce7fb1ce,0x706c1c70,0xa60daba6,0x27edca27,0x20280820,0xa348eba3,0x56c19756,0x2808202,0x7fa3dc7f,0x52c49652,0xeb12f9eb,0xd5a174d5,0x3eb38d3e,0xfcc33ffc,0x9a3ea49a,
0x1d5b461d,0x1c1b071c,0x9e3ba59e,0xf30cfff3,0xcf3ff0cf,0xcdbf72cd,0x5c4b175c,0xea52b8ea,0xe8f810e,0x653d5865,0xf0cc3cf0,0x647d1964,0x9b7ee59b,0x16918716,0x3d734e3d,0xa208aaa2,
0xa1c869a1,0xadc76aad,0x6858306,0xca7ab0ca,0xc5b570c5,0x91f46591,0x6bb2d96b,0x2ea7892e,0xe318fbe3,0xaf47e8af,0x3c330f3c,0x2d674a2d,0xc1b071c1,0x590e5759,0x76e99f76,0xd4e135d4,
0x78661e78,0x90b42490,0x38360e38,0x79265f79,0x8def628d,0x61385961,0x4795d247,0x8a2aa08a,0x94b12594,0x88aa2288,0xf18c7df1,0xecd73bec,0x4050104,0x84a52184,0xe19879e1,0x1e9b851e,
0x5384d753,0x0,0x195e4719,0x5d0b565d,0x7ee39d7e,0x4f9fd04f,0x9cbb279c,0x491a5349,0x317c4d31,0xd8ee36d8,0x80a0208,0x9f7be49f,0x8220a282,0x13d4c713,0x23e8cb23,0x7ae69c7a,
0xab42e9ab,0xfe43bdfe,0x2aa2882a,0x4b9ad14b,0x1404101,0x1fdbc41f,0xe0d838e0,0xd661b7d6,0x8e2fa18e,0xdf2bf4df,0xcb3af1cb,0x3bf6cd3b,0xe71dfae7,0x85e56085,0x54411554,0x8625a386,
0x8360e383,0xba16acba,0x75295c75,0x9234a692,0x6ef7996e,0xd0e434d0,0x68721a68,0x55015455,0xb619afb6,0x4edf914e,0xc8fa32c8,0xc0f030c0,0xd721f6d7,0x32bc8e32,0xc675b3c6,0x8f6fe08f,
0x74691d74,0xdb2ef5db,0x8b6ae18b,0xb8962eb8,0xa8a800a,0x99fe6799,0x2be2c92b,0x81e06181,0x3c0c303,0xa48d29a4,0x8caf238c,0xae07a9ae,0x34390d34,0x4d1f524d,0x39764f39,0xbdd36ebd,
0x5781d657,0x6fb7d86f,0xdceb37dc,0x15514415,0x7ba6dd7b,0xf709fef7,0x3ab68c3a,0xbc932fbc,0xc0f030c,0xff03fcff,0xa9c26ba9,0xc9ba73c9,0xb5d96cb5,0xb1dc6db1,0x6d375a6d,0x45155045,
0x36b98f36,0x6c771b6c,0xbe13adbe,0x4ada904a,0xee57b9ee,0x77a9de77,0xf24cbef2,0xfd837efd,0x44551144,0x67bdda67,0x712c5d71,0x5454005,0x7c631f7c,0x40501040,0x69325b69,0x63b8db63,
0x28220a28,0x7c5c207,0xc4f531c4,0x22a88a22,0x9631a796,0x37f9ce37,0xed977aed,0xf649bff6,0xb4992db4,0xd1a475d1,0x4390d343,0x485a1248,0xe258bae2,0x9771e697,0xd264b6d2,0xc270b2c2,
0x26ad8b26,0xa5cd68a5,0x5ecb955e,0x29624b29,0x303c0c30,0x5ace945a,0xddab76dd,0xf9867ff9,0x95f16495,0xe65dbbe6,0xc735f2c7,0x242d0924,0x17d1c617,0xb9d66fb9,0x1bdec51b,0x12948612,
0x60781860,0xc330f3c3,0xf5897cf5,0xb35cefb3,0xe8d23ae8,0x73acdf73,0x35794c35,0x80a02080,0xe59d78e5,0xbb56edbb,0x7d235e7d,0xf8c63ef8,0x5f8bd45f,0x2fe7c82f,0xe4dd39e4,0x21684921
};
static const uint32_t TboxTable0[256] = {
    0x8ed55b5b,0xd0924242,0x4deaa7a7,0x6fdfbfb,0xfccf3333,0x65e28787,0xc93df4f4,0x6bb5dede,0x4e165858,0x6eb4dada,0x44145050,0xcac10b0b,0x8828a0a0,0x17f8efef,0x9c2cb0b0,0x11051414,
0x872bacac,0xfb669d9d,0xf2986a6a,0xae77d9d9,0x822aa8a8,0x46bcfafa,0x14041010,0xcfc00f0f,0x2a8aaaa,0x54451111,0x5f134c4c,0xbe269898,0x6d482525,0x9e841a1a,0x1e061818,0xfd9b6666,
0xec9e7272,0x4a430909,0x10514141,0x24f7d3d3,0xd5934646,0x53ecbfbf,0xf89a6262,0x927be9e9,0xff33cccc,0x4555151,0x270b2c2c,0x4f420d0d,0x59eeb7b7,0xf3cc3f3f,0x1caeb2b2,0xea638989,
0x74e79393,0x7fb1cece,0x6c1c7070,0xdaba6a6,0xedca2727,0x28082020,0x48eba3a3,0xc1975656,0x80820202,0xa3dc7f7f,0xc4965252,0x12f9ebeb,0xa174d5d5,0xb38d3e3e,0xc33ffcfc,0x3ea49a9a,
0x5b461d1d,0x1b071c1c,0x3ba59e9e,0xcfff3f3,0x3ff0cfcf,0xbf72cdcd,0x4b175c5c,0x52b8eaea,0x8f810e0e,0x3d586565,0xcc3cf0f0,0x7d196464,0x7ee59b9b,0x91871616,0x734e3d3d,0x8aaa2a2,
0xc869a1a1,0xc76aadad,0x85830606,0x7ab0caca,0xb570c5c5,0xf4659191,0xb2d96b6b,0xa7892e2e,0x18fbe3e3,0x47e8afaf,0x330f3c3c,0x674a2d2d,0xb071c1c1,0xe575959,0xe99f7676,0xe135d4d4,
0x661e7878,0xb4249090,0x360e3838,0x265f7979,0xef628d8d,0x38596161,0x95d24747,0x2aa08a8a,0xb1259494,0xaa228888,0x8c7df1f1,0xd73becec,0x5010404,0xa5218484,0x9879e1e1,0x9b851e1e,
0x84d75353,0x0,0x5e471919,0xb565d5d,0xe39d7e7e,0x9fd04f4f,0xbb279c9c,0x1a534949,0x7c4d3131,0xee36d8d8,0xa020808,0x7be49f9f,0x20a28282,0xd4c71313,0xe8cb2323,0xe69c7a7a,
0x42e9abab,0x43bdfefe,0xa2882a2a,0x9ad14b4b,0x40410101,0xdbc41f1f,0xd838e0e0,0x61b7d6d6,0x2fa18e8e,0x2bf4dfdf,0x3af1cbcb,0xf6cd3b3b,0x1dfae7e7,0xe5608585,0x41155454,0x25a38686,
0x60e38383,0x16acbaba,0x295c7575,0x34a69292,0xf7996e6e,0xe434d0d0,0x721a6868,0x1545555,0x19afb6b6,0xdf914e4e,0xfa32c8c8,0xf030c0c0,0x21f6d7d7,0xbc8e3232,0x75b3c6c6,0x6fe08f8f,
0x691d7474,0x2ef5dbdb,0x6ae18b8b,0x962eb8b8,0x8a800a0a,0xfe679999,0xe2c92b2b,0xe0618181,0xc0c30303,0x8d29a4a4,0xaf238c8c,0x7a9aeae,0x390d3434,0x1f524d4d,0x764f3939,0xd36ebdbd,
0x81d65757,0xb7d86f6f,0xeb37dcdc,0x51441515,0xa6dd7b7b,0x9fef7f7,0xb68c3a3a,0x932fbcbc,0xf030c0c,0x3fcffff,0xc26ba9a9,0xba73c9c9,0xd96cb5b5,0xdc6db1b1,0x375a6d6d,0x15504545,
0xb98f3636,0x771b6c6c,0x13adbebe,0xda904a4a,0x57b9eeee,0xa9de7777,0x4cbef2f2,0x837efdfd,0x55114444,0xbdda6767,0x2c5d7171,0x45400505,0x631f7c7c,0x50104040,0x325b6969,0xb8db6363,
0x220a2828,0xc5c20707,0xf531c4c4,0xa88a2222,0x31a79696,0xf9ce3737,0x977aeded,0x49bff6f6,0x992db4b4,0xa475d1d1,0x90d34343,0x5a124848,0x58bae2e2,0x71e69797,0x64b6d2d2,0x70b2c2c2,
0xad8b2626,0xcd68a5a5,0xcb955e5e,0x624b2929,0x3c0c3030,0xce945a5a,0xab76dddd,0x867ff9f9,0xf1649595,0x5dbbe6e6,0x35f2c7c7,0x2d092424,0xd1c61717,0xd66fb9b9,0xdec51b1b,0x94861212,
0x78186060,0x30f3c3c3,0x897cf5f5,0x5cefb3b3,0xd23ae8e8,0xacdf7373,0x794c3535,0xa0208080,0x9d78e5e5,0x56edbbbb,0x235e7d7d,0xc63ef8f8,0x8bd45f5f,0xe7c82f2f,0xdd39e4e4,0x68492121
};
static const uint8_t SboxTable[256] = {

    0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05,
    0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99,
    0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62,
    0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6,
    0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8,
    0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35,
    0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87,
    0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e,
    0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1,
    0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3,
    0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f,
    0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51,
    0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8,
    0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0,
    0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84,
    0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48
};

const uint32_t FK[4] = { 0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc };

const uint32_t CK[32] = {
    0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
    0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
    0xe0e7eeF5, 0xfc030a11, 0x181f262d, 0x343b4249,
    0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
    0xc0c7ced5, 0xdce3eafb, 0xf8ff060d, 0x141b2229,
    0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
    0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
    0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
};

// 辅助函数（循环左移）
uint32_t rotate_left(uint32_t x, uint8_t n) {
    return (x << n) | (x >> (32 - n));
}

// T变换
uint32_t T(uint32_t x) {
    return rotate_left(x, 2) ^ rotate_left(x, 10) ^ rotate_left(x, 18) ^ rotate_left(x, 24);
}

// T' 变换
uint32_t T_prime(uint32_t x) {
    return rotate_left(x, 13) ^ rotate_left(x, 23);
}

uint32_t nonlinear_transform(uint32_t x) {
    uint8_t a0 = x >> 24;
    uint8_t a1 = x >> 16;
    uint8_t a2 = x >> 8;
    uint8_t a3 = x;

    a0 = SboxTable[a0];
    a1 = SboxTable[a1];
    a2 = SboxTable[a2];
    a3 = SboxTable[a3];

    return (a0 << 24) | (a1 << 16) | (a2 << 8) | a3;
}

uint32_t L(uint32_t b) {
    return b ^ rotate_left(b, 2) ^ rotate_left(b, 10) ^ rotate_left(b, 18) ^ rotate_left(b, 24);
}

uint32_t key_evolution_function(uint32_t x) {
    return L(nonlinear_transform(x));
}

//密钥拓展
void key_expansion(const uint32_t* key, uint32_t* round_keys) {
    uint32_t k[4];

    for (int i = 0; i < 4; i++) {
        k[i] = key[i] ^ FK[i];
    }

    for (int i = 0; i < 32; i++) {
        k[i % 4] ^= key_evolution_function(k[(i + 1) % 4] ^ k[(i + 2) % 4] ^ k[(i + 3) % 4] ^ CK[i]);
        round_keys[i] = k[i % 4];
    }
}

uint32_t F(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t rk) {
    return x0 ^ L(nonlinear_transform(x1 ^ x2 ^ x3 ^ rk));
}
uint32_t T1(uint32_t x) {
    uint8_t a0 = x >> 24;
    uint8_t a1 = x >> 16;
    uint8_t a2 = x >> 8;
    uint8_t a3 = x;

    uint32_t a00 = TboxTable0[a0];
    uint32_t a11 = TboxTable1[a1];
    uint32_t a22 = TboxTable2[a2];
    uint32_t a33 = TboxTable3[a3];

    return a00 ^ a11 ^ a22 ^ a33;
}

uint64_t T12(uint64_t x) {
    uint8_t a0 = x >> 56;
    uint8_t a1 = x >> 48;
    uint8_t a2 = x >> 40;
    uint8_t a3 = x >> 32;
    uint8_t a4 = x >> 24;
    uint8_t a5 = x >> 16;
    uint8_t a6 = x >> 8;
    uint8_t a7 = x;

    uint64_t a00 = (static_cast<uint64_t>(TboxTable0[a0]) << 32) | TboxTable0[a4];
    uint64_t a11 = (static_cast<uint64_t>(TboxTable1[a1]) << 32) | TboxTable1[a5];
    uint64_t a22 = (static_cast<uint64_t>(TboxTable2[a2]) << 32) | TboxTable2[a6];
    uint64_t a33 = (static_cast<uint64_t>(TboxTable3[a3]) << 32) | TboxTable3[a7];
    //std::cout << std::hex <<"hellowold:" <<( a00 ^ a11 ^ a22 ^ a33) << '\n';
    return a00 ^ a11 ^ a22 ^ a33;
}

__m256i T13(__m256i result) {
    uint8_t temp[32]; // 假设 __m256i 变量包含 32 个 8 位元素
    _mm256_storeu_si256((__m256i*)temp, result);
    int a1[8], a2[8], a3[8], a0[8];
    // 将提取的字节存储在目标数组中
    for (int j = 0; j < 8; j++) {
        a0[j] = temp[j * 4 + 0];
        a1[j] = temp[j * 4 + 1];
        a2[j] = temp[j * 4 + 2];
        a3[j] = temp[j * 4 + 3];
    }
    __m256i vindex = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
    __m256i a00, a11, a22, a33;
    a00 = _mm256_i32gather_epi32(a0, vindex,4);
    a11 = _mm256_i32gather_epi32(a1, vindex, 4);
    a22 = _mm256_i32gather_epi32(a2, vindex, 4);
    a33 = _mm256_i32gather_epi32(a3, vindex, 4);
    a00=_mm256_i32gather_epi32((int*)TboxTable0, a00, 4);
    a11 = _mm256_i32gather_epi32((int*)TboxTable1, a11, 4);
    a22 = _mm256_i32gather_epi32((int*)TboxTable2, a22, 4);
    a33 = _mm256_i32gather_epi32((int*)TboxTable3, a33, 4);

    __m256i temp1 = _mm256_xor_si256(a00, a11);
    __m256i temp2 = _mm256_xor_si256(a22, a33);

    return _mm256_xor_si256(temp1, temp2);
}
uint32_t F11(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t rk) {
    return x0 ^ T1(x1 ^ x2 ^ x3 ^ rk);
}

uint64_t F12(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t rk) {
    //std::cout << std::hex << "hellowold:" << (x0 ^ T12(x1 ^ x2 ^ x3 ^ rk)) << '\n';
    return x0 ^ T12(x1 ^ x2 ^ x3 ^ rk);
}

__m256i F13(__m256i a, __m256i b, __m256i c, __m256i d, __m256i key) {
    __m256i temp1 = _mm256_xor_si256(a, b);
    __m256i temp2 = _mm256_xor_si256(c, d);
    __m256i result = _mm256_xor_si256(temp1, temp2);
    result = T13(result);
    return _mm256_xor_si256(result, key);
}


void sm4_encrypt(const uint32_t* plaintext, const uint32_t* round_keys, uint32_t* ciphertext) {
    uint32_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = plaintext[i];
    }

    for (int i = 0; i < 32; ++i) {
        uint32_t t = F(x[0], x[1], x[2], x[3], round_keys[i]);
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        ciphertext[3 - i] = x[i];
    }
}

void sm4_encrypt1(const uint32_t* plaintext, const uint32_t* round_keys, uint32_t* ciphertext) {
    uint32_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = plaintext[i];
    }

    for (int i = 0; i < 32; ++i) {
        uint32_t t = F11(x[0], x[1], x[2], x[3], round_keys[i]);
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        ciphertext[3 - i] = x[i];
    }
}
void sm4_encrypt2(const uint32_t* plaintext, const uint32_t* round_keys, uint32_t* ciphertext) {
    uint64_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = static_cast<uint64_t>(plaintext[i])<<32 | plaintext[i+4];
        //std::cout << std::hex << x[i] <<'\t'<< plaintext[i] << '\n';
    }

    for (int i = 0; i < 32; ++i) {
       uint64_t rk = static_cast<uint64_t>(round_keys[i] )<< 32 | round_keys[i];
        uint64_t t = F12(x[0], x[1], x[2], x[3], rk);
        //std::cout << std::hex << x[0] << '\n';
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        ciphertext[3 - i] = x[i] >> 32;
        ciphertext[7 - i] = x[i];
        //std::cout << std::hex << x[i] << '\t' << ciphertext[3 - i] << '\t' << ciphertext[7 - i] << '\n';
    }
}

void sm4_encrypt3(const uint32_t* plaintext, const uint32_t* round_keys, uint32_t* ciphertext, int i) {
    __m256i vindex, R0, R1, R2, R3,rk,Rmiddle;
    vindex = _mm256_setr_epi32(0, 4, 8, 12, 16, 20, 24, 28);
    R0 = _mm256_i32gather_epi32((int*)(plaintext + 4 * 0+i*32), vindex, 4);
    R1 = _mm256_i32gather_epi32((int*)(plaintext + 4 * 1+i*32), vindex, 4);
    R2 = _mm256_i32gather_epi32((int*)(plaintext + 4 * 2+i*32), vindex, 4);
    R3 = _mm256_i32gather_epi32((int*)(plaintext + 4 * 3+i*32), vindex, 4);
    for (int i = 0; i < 32; ++i) {
        __m256i index = _mm256_setzero_si256();
        rk = _mm256_i32gather_epi32((int*)(round_keys + i),index,4);
        __m256i t = F13(R0, R1, R2,R3, rk);
        R0 =R1;
        R1=R2;
        R2 = R3;
        R3 = t;
    }
    int temp[4][8]; // 假设 __m256i 变量包含 32 个 8 位元素
    _mm256_storeu_si256((__m256i*)temp[0], R3);
    _mm256_storeu_si256((__m256i*)temp[1], R2);
    _mm256_storeu_si256((__m256i*)temp[2], R1);
    _mm256_storeu_si256((__m256i*)temp[3], R0);
    for (int k = 0; k < 8; k++) {
        for (int j = 0; j < 4; j++) {
            ciphertext[i * 32 + k * 4 + j] = temp[j][k];
        }
    }
    
}
void sm4_decrypt(const uint32_t* ciphertext, const uint32_t* round_keys, uint32_t* plaintext) {
    uint32_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = ciphertext[i];//<<32 | ciphertext[i+4];
    }

    for (int i = 0; i < 32; ++i) {
        //uint64_t rk = static_cast<uint64_t>(round_keys[31 - i]) << 32 | round_keys[31 - i];
        uint32_t t = F(x[0], x[1], x[2], x[3], round_keys[31 - i]);
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        plaintext[3 - i] = x[i];//>> 32;
    }
}

void sm4_decrypt1(const uint32_t* ciphertext, const uint32_t* round_keys, uint32_t* plaintext) {
    uint32_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = ciphertext[i];//<<32 | ciphertext[i+4];
    }

    for (int i = 0; i < 32; ++i) {
        //uint64_t rk = static_cast<uint64_t>(round_keys[31 - i]) << 32 | round_keys[31 - i];
        uint32_t t = F11(x[0], x[1], x[2], x[3], round_keys[31 - i]);
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        plaintext[3 - i] = x[i];//>> 32;
    }
}

void sm4_decrypt2(const uint32_t* ciphertext, const uint32_t* round_keys, uint32_t* plaintext) {
    uint64_t x[4];
    for (int i = 0; i < 4; ++i) {
        x[i] = static_cast<uint64_t>(ciphertext[i])<<32 | ciphertext[i+4];
    }

    for (int i = 0; i < 32; ++i) {
        uint64_t rk = static_cast<uint64_t>(round_keys[31 - i]) << 32 | round_keys[31 - i];
        uint64_t t = F12(x[0], x[1], x[2], x[3], rk);
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;
    }

    for (int i = 0; i < 4; ++i) {
        plaintext[3 - i] = x[i]>> 32;
        plaintext[7 - i] = x[i];
    }
}

void uint32_to_uint8(const uint32_t* input, uint8_t* output, size_t len) {
    for (size_t i = 0; i < len; i++) {
        output[i * 4 + 0] = (input[i] >> 24) & 0xff;
        output[i * 4 + 1] = (input[i] >> 16) & 0xff;
        output[i * 4 + 2] = (input[i] >> 8) & 0xff;
        output[i * 4 + 3] = input[i] & 0xff;
    }
}
void read_input(uint8_t* input_data, int i, uint32_t plaintext1[4]) {
    plaintext1[0] = input_data[i * 16 + 0] << 24 ^ input_data[i * 16 + 1] << 16 ^ input_data[16 * i + 2] << 8 ^ input_data[16 * i + 3];
    plaintext1[1] = input_data[i * 16 + 4] << 24 ^ input_data[i * 16 + 5] << 16 ^ input_data[16 * i+ 6] << 8 ^ input_data[16 * i + 7];
    plaintext1[2] = input_data[i * 16 + 8] << 24 ^ input_data[i * 16 + 9] << 16 ^ input_data[16 * i + 10] << 8 ^ input_data[16 * i + 11];
    plaintext1[3] = input_data[i * 16 + 12] << 24 ^ input_data[i * 16 + 13] << 16 ^ input_data[16 * i + 14] << 8 ^ input_data[16 * i + 15];

}

void read_output(uint8_t* input_data, int i, uint32_t plaintext1[4]) {
    input_data[i * 16 + 0] = plaintext1[0] >> 24;
    input_data[i * 16 + 1] = plaintext1[0] >> 16; 
    input_data[16 * i + 2] = plaintext1[0] >> 8;
    input_data[16 * i + 3] = plaintext1[0] ;
    input_data[i * 16 + 4] = plaintext1[1] >> 24; input_data[i * 16 + 5] = plaintext1[1] >> 16; input_data[16 * i + 6] = plaintext1[1] >> 8; input_data[16 * i + 7] = plaintext1[1] ;
    input_data[i * 16 + 8] = plaintext1[2] >> 24; input_data[i * 16 + 9] = plaintext1[2] >> 16; input_data[16 * i + 10] = plaintext1[2] >> 8; input_data[16 * i + 11] = plaintext1[2];
    input_data[i * 16 + 12] = plaintext1[3] >> 24; input_data[i * 16 + 13] = plaintext1[3] >> 16; input_data[16 * i + 14] = plaintext1[3] >> 8; input_data[16 * i + 15] = plaintext1[3];

}

void sm4_top0(
    uint8_t* input_data,
    int input_size,
    uint32_t key[4],
    uint8_t* output_data
) {
    // 密钥扩展
    uint32_t rk[32];
    key_expansion(key, rk);
    uint32_t plaintext1[4];
    uint32_t ciphertext1[4];
    uint32_t decrypted1[4];
    for (int i = 0; i < input_size / 16; i++) {
        read_input(input_data, i, plaintext1);
        sm4_encrypt(plaintext1, rk, ciphertext1);
        //sm4_decrypt1(ciphertext1, rk, decrypted1);
        read_output(input_data, i, ciphertext1);
        // 逐个处理128位数据块
    }
}
void sm4_top(
    uint8_t *input_data,
    int input_size,
    uint32_t key[4],
    uint8_t *output_data
) {
    // 密钥扩展
    uint32_t rk[32];
    key_expansion(key, rk);
    uint32_t plaintext1[4];
    uint32_t ciphertext1[4];
    uint32_t decrypted1[4];
    for (int i = 0; i < input_size/16; i++) {
        read_input(input_data, i, plaintext1);
        sm4_encrypt1(plaintext1, rk, ciphertext1);
        //sm4_decrypt1(ciphertext1, rk, decrypted1);
        read_output(input_data, i, ciphertext1);
        // 逐个处理128位数据块
    }
}

void sm4_top2(
    uint8_t* input_data,
    int input_size,
    uint32_t key[4],
    uint8_t* output_data
) {
    // 密钥扩展
    uint32_t rk[32];
    key_expansion(key, rk);
    uint32_t plaintext1[8];
    uint32_t ciphertext1[8];
    uint32_t decrypted1[8];
    for (int i = 0; i < input_size /16; i+=2) {
       read_input(input_data, i, plaintext1);
        read_input(input_data, i+1, plaintext1+4);
        sm4_encrypt2(plaintext1, rk, ciphertext1);
        //sm4_decrypt2(ciphertext1, rk, decrypted1);
       read_output(input_data, i, ciphertext1);
        read_output(input_data, i+1, ciphertext1+4);
    }
}

void sm4_top3(
    uint32_t* input_data,
    int input_size,
    uint32_t key[4],
    uint32_t* output_data
) {
    // 密钥扩展
    int hello = input_size /32;
    hello *= 32;
    uint32_t rk[32];
    key_expansion(key, rk);
    for (int i = 0; i < hello / 32; i += 2) {
        sm4_encrypt3(input_data, rk, output_data,i);
       // sm4_decrypt2(ciphertext1, rk, decrypted1);
    }
    uint32_t plaintext1[4];
    uint32_t ciphertext1[4];
    for (int j = hello; j < input_size/4; j++) {
        sm4_encrypt1(input_data+hello+j, rk, output_data + hello + j);
    }
}

int main() {
    const char* input_file_name = "C:\\Users\\lenovo\\AppData\\Roaming\\Xilinx\\Vivado\\sm41\\video.mp4";
    FILE* input_file = fopen(input_file_name, "rb");
    if (input_file == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }


    // 获取文件大小
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    // 分配内存并读取文件内容
    uint8_t* file_data = (uint8_t*)malloc(file_size);
    fread(file_data, 1, file_size, input_file);
    fclose(input_file);
    std::cout <<"文件大小为: " << file_size << '\n';
    size_t encrypted_data_size = ((file_size + 15) / 16) * 16;
    uint8_t* input_dataa = nullptr;
    uint8_t* output_dataa = nullptr;
    uint8_t* output_dataaa = nullptr;
    uint32_t* input_data = nullptr;
    uint32_t* output_data = nullptr;
    // 分配内存并读取文件内容
    input_dataa = (uint8_t*)malloc(1000000);
    input_data = (uint32_t*)malloc(1000000);
    memcpy(input_dataa, file_data, file_size);
    // 补足输入数据以使其长度为128位的倍数
    for (int i = file_size; i < encrypted_data_size; ++i) {
        input_dataa[i] = 0;
    }
    for (int i = 0; i < (encrypted_data_size/4); ++i) {
        for(int j=0;j<4;j++)
        input_data[i] = input_data[i]^(static_cast<uint32_t>(input_dataa[i*4+j])<<((3-j)*8));
    }

    output_data = (uint32_t*)malloc(1000000);
    output_dataa = (uint8_t*)malloc(1000000);
    output_dataaa = (uint8_t*)malloc(1000000);



    uint32_t key[4] = { 0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210 };
    uint32_t rk[32];
    key_expansion(key, rk);

    clock_t custom_start = clock();
    key_expansion(key, rk);

    sm4_top0(input_dataa, encrypted_data_size, key, output_dataaa);
    clock_t custom_end = clock();
    double custom_time = ((double)(custom_end - custom_start)) / (CLOCKS_PER_SEC);
    printf("normal sm4  Custom SM4 implementation time: %f seconds\n", custom_time);

     custom_start = clock();
    key_expansion(key, rk);

    sm4_top(input_dataa, encrypted_data_size, key, output_dataaa);
     custom_end = clock();
     custom_time = ((double)(custom_end - custom_start)) / (CLOCKS_PER_SEC);
    printf("Tbox sm4 Custom SM4 implementation time: %f seconds\n", custom_time);

    custom_start = clock();
    key_expansion(key, rk);
   
    sm4_top2(input_dataa, encrypted_data_size, key, output_dataa);
    custom_end = clock();
    custom_time = ((double)(custom_end - custom_start)) / (CLOCKS_PER_SEC);
    printf("64bitreg sm4  Custom SM4 implementation time: %f seconds\n", custom_time);
    custom_start = clock();
    key_expansion(key, rk);
 
    sm4_top3(input_data, encrypted_data_size / 4, key, output_data);
 
    custom_end = clock();
    custom_time = ((double)(custom_end - custom_start)) / (CLOCKS_PER_SEC );
    printf("SIMD sm4 Custom SM4 implementation time: %f seconds\n", custom_time);
    if (memcmp(output_dataaa, output_dataa, sizeof(output_dataa)) != 0) {
        printf("Custom SM4 implementation correctness test failed\n");
        return 1;
    }

    return 0;


}
