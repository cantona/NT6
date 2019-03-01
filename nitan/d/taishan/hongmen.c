// Room: /d/taishan/hongmen.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "紅門宮");
        set("long", @LONG
紅門宮東臨中溪，西靠大藏嶺，是泰山中溪的門戶，呈半封閉凹形
空間。再加宮前三重白色石坊及碑碣，構成一組高低錯落、色彩鮮明、
形若天梯的古建築群。自飛雲閣洞北望，林蔭夾道，石級綿延。自古有
“紅門曉日”之景。清人趙國麟留詩：“凌晨登紅門，霽色明朝旭。俯
視萬家煙，平疇盡新綠。”
LONG );
        set("exits", ([
                "east"      : __DIR__"mileyuan",
                "northeast" : __DIR__"xiaodongtian",
                "northup"   : __DIR__"yitian",
                "southdown" : __DIR__"baihe",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 80);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}