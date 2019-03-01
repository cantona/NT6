// Room: /d/suzhou/dxbaodian.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "大雄寶殿");
        set("long",@long
這裡是靈巖寺的大雄寶殿。正中供奉著如來三寶，左右各是文殊、
普賢菩薩。一群青衣小和尚們正在佛像前的地上誦經。縷縷香煙與梵唱
交錯在一起，仰視佛祖拈花淺笑的面容，令人頓時生起幾分脫俗之感。
身邊經常有一隊隊僧人魚貫而入，看他們手持戒刀，似乎是巡寺的僧人。
long);
        set("exits",([
                "out"   : __DIR__"lingyansi",
                "north" : __DIR__"cangjingge",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1119);
	set("coor/y", -1161);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}