inherit ROOM;
void create()
{
        set("short", "揚刀立威會場");
        set("long", @LONG
這裏是揚刀立威會場，一片青草地上擺着七八張方桌，除了東首第一席外，
每張桌旁都已坐了人，有海沙派、巨鯨幫、神拳門等等各派弟子。
LONG );

        set("exits", ([
                "west" : "/d/tulong/tulong/gukou",
                ]));

        set("objects", ([
                "/d/tulong/tulong/npc/mai" : 1,
                "/d/tulong/tulong/npc/guo" : 1,
                "/d/tulong/tulong/npc/yin" : 1,
                "/d/tulong/tulong/npc/yuan" : 1,
                "/d/tulong/tulong/obj/ding" : 1,
                "/d/tulong/tulong/npc/zhang" : 1,
                "/d/tulong/tulong/npc/chang" : 1,
                ]));
setup();
}
