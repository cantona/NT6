// fu-midao.c 密道
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裡是侯員外臥室下的密道，聽說許多佃戶由于繳不起租，
被侯員外的爪牙抓到這裡來拷打。四周好象有一些淺褐色幹的血
漬，空氣中夾雜著一種令人毛骨悚然的腥氣。你不由地有些害怕
起來，心想還是趕快離開這裡吧。
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