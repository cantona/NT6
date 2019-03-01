inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
你走在一條堅實的石階上，不時地有進香客從你的身邊走過。一
邊是峭壁，一邊是懸崖，抬頭隱約可見籠罩在雲霧中的天柱峰，聽著
流水淙淙，令人心曠神怡。北邊是一座牌坊。
LONG );
        set("objects", ([
                __DIR__"npc/guest" : 1,
        ]));
        set("exits", ([
                "northdown" : __DIR__"shibapan",
                "southup" : __DIR__"zixiaogate",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -370);
        set("coor/y", -270);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}