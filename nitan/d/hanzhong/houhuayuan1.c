// houhuayuan1.c 後花園
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後花園");
        set("long", @LONG
這是一片荒廢了的花園，本來這裡有一片小池塘，養著一些
金魚之類，現在池塘差不多也幹涸了。池塘邊立著一座假山，山
上長滿了青苔，看來已經很久沒有人來過了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "west" : __DIR__"houhuayuan",
        ]));
        set("objects", ([
                __DIR__"npc/wugui" : 1,
        ] ));

        set("coor/x", -12220);
	set("coor/y", 760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}