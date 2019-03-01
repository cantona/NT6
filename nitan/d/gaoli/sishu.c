// /d/gaoli/sishi
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "私塾");
        set("long", @LONG
你來到一間寬敞明亮的房間，只見四壁排滿了書架，書架上的書籍
從諸子百家到詩詞歌賦應有盡有。房間當中有一紫檀書桌，靠窗牆上懸
掛著一副字畫，一位老先生坐在桌後。
LONG
        );
set("exits", ([
               "west":__DIR__"xuanwu-2", 
        ]));
      set("objects", ([
                "/d/gaoli/npc/xuejiu" : 1,
                __DIR__"npc/gongzi2":1,
        ]));
       setup();
        replace_program(ROOM);
}        
