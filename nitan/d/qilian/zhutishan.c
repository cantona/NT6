// Room: /d/qilian/zhutishan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "朱提山");
        set("long", @LONG
此山通山由赤土構成，遠望尤如紅瑪瑙帽頂，所以叫朱提。其山為
祈連諸山中最矮的一座，大概因為土質不好，少有生跡，唯山頂有幾處
黑草叢生之處。但聽説常有劇毒長蟲出沒，令人頗感費解。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "northdown" : __DIR__"yongchang",
                "southwest" : __DIR__"datongling",
        ]));
        set("objects", ([
                "/d/shenlong/npc/fushe" : random(2),
                "/d/shenlong/npc/dushe" : random(2),
        ]));
        set("coor/x", -5000);
        set("coor/y", 10000);
        set("coor/z", 5);
        setup();
        replace_program(ROOM);
}