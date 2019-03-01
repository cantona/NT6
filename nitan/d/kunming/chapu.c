inherit ROOM;

void create()
{
        set("short", "聚朋茶館");
        set("long", @LONG
幾張方桌，幾個方凳，茶館的設施雖然簡陋，卻是一個大
好去處，許多人在這裡談天說地，你可以在這裡打聽到許多的
奇聞佚事，所以城裡城外的人沒事都會來這裡座一座，抽上幾
口水煙，天南地北的聊聊。
LONG);
        set("resource/water", 1);
        set("exits", ([
                "west" : __DIR__"nandajie2",
        ]));

        set("objects", ([
                __DIR__"npc/chaxiaoer" : 1,
                __DIR__"npc/obj/yantong":1,
        ]));

	set("coor/x", -16830);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}