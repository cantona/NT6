// laojun.c

inherit ROOM;

void create()
{
        set("short", "老君溝");
        set("long", @LONG
爬過兩個要命的懸崖，可在這裏稍作歇息。老君溝是一條半里多
長的山溝，相傳為太上老君到此，見無路可通，因而套上大青牛用鐵
犁犁出了這條溝作為登山通道。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "westdown" : __DIR__"pingxinshi",
            "southup"  : __DIR__"husun",
            "north"    : __DIR__"liyubei",            
        ]));
        set("objects", ([
             "/kungfu/class/huashan/lao" : 1,
        ]));

        set("outdoors", "huashan" );

        setup();

}
 
/*
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("lao denuo", this_object())))
                return 1;

        if (dir == "southup")
                return guarder->permit_pass(me, dir);

        return 1;
}
*/