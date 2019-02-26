inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這時雪更大些了，使得地上蓋上了厚厚的一層。正值朝陽初
出，從山頂倒掛下來的冰川，由於太陽光的折射和發射，整個冰
層都變成淺藍色的透明體，那些末曾凝結的雪花，在陽光底下，
泛出霞輝麗彩，奇妙得難以形容。山路也漸漸不平坦起來，走一
步跌三步，聯想到古詩所説：“去時雪滿天山路”，也不過如此
吧。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "southdown"  : __DIR__"sroad1",
                    "northup"  : __DIR__"sroad3",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
