// huashi.c
inherit ROOM;

void create()
{
        set("short", "畫室");
        set("long", @LONG
這裏是丹青生的畫室，俗話説：書畫不分家，所以丹青生的書法
也有相當的功力，雖然不及他三哥禿筆翁很多，但他將他的劍法融於
他的書法當中，也可謂是銀鈎鐵畫了。這裏的陳設和書室差不多，唯
一不同的是這裏的牆上並沒有掛丹青生的丹青妙筆，而是掛了許多前
朝名家的名畫，屬於丹青生自己的是一幅寫着《兵車行》的中堂。
LONG );
        set("exits", ([
                "west" : __DIR__"zoulang1",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/danqing" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}