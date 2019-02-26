// Room: /d/wuxi/shuyuan.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "東林書院");
        set("long", @LONG
東林書院是無錫最有名的講堂，這裏窗明几淨，一塵不染。書院裏
聚集了江南一帶最有名的學儒和才子。他們大多是一些失意歸田的舊官
員，在這裏傳授平生所學，共議天下形勢。書案上擺着幾本翻開了的線
裝書籍。後面是一個書架(shujia)。講堂內多嵌着歷代楹聯石刻，足見
書院歷史的悠久。左壁是學規(xuegui)。
LONG );
        set("exits", ([
                "south" : __DIR__"shuyuangate",
        ]));
        set("item_desc", ([
                "xuegui" : "
日講經書三起，日看綱目數頁。
通曉時務物理，參讀古文詩賦。
讀書必須過筆，會課按時蚤完。
夜讀仍戒晏起，疑誤定要力爭。

求學需繳學費五十兩
 \n",
        ]));
        set("objects", ([
                __DIR__"npc/gu" : 1,
        ]));
        set("coor/x", 1060);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}