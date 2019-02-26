inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是練功房，地下凌亂地放着幾個蒲團，幾位武當弟子正盤膝
坐在上面打坐。
LONG );
        set("exits", ([
                "west" : __DIR__"donglang2",
        ]));
        set("objects", ([
                "/d/village/obj/zhujian" : 3
        ]));
        set("coor/x", -340);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
}