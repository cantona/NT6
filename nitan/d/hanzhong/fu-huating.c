// fu-huating 花廳
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "花廳");
        set("long", @LONG
這裏是這户人家喝酒賞月的所在，一個小亭子建造在廳的中央，
四周圍繞着一些葡萄藤(teng)。一陣微風吹過，空氣中似乎有隱隱
的花香飄來，中人慾醉。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "south" : __DIR__"fu-ceting",
                "west" : __DIR__"fu-xiaoyuan",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
            "teng": "這些藤好像長得有些日子了，密不透風，夏天呆在藤下肯定陰涼極了。\n"
        ]) );
        set("coor/x", -12230);
	set("coor/y", 790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}