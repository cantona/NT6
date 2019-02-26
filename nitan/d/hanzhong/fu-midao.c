// fu-midao.c 密道
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裏是侯員外卧室下的密道，聽説許多佃户由於繳不起租，
被侯員外的爪牙抓到這裏來拷打。四周好像有一些淺褐色乾的血
漬，空氣中夾雜着一種令人毛骨悚然的腥氣。你不由地有些害怕
起來，心想還是趕快離開這裏吧。
LONG
        );
        set("exits", ([
                "southeast" : __DIR__"fu-mishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", -50);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}