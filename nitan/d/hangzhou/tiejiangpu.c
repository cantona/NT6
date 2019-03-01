// tiejiangpu.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "鐵匠鋪");
        set("long", @LONG
這是一家不小的打鐵鋪，店裏擺了幾座火爐，一位鐵匠正在火爐
旁滿頭大汗地打造東西。一位老者坐在邊上。火爐邊放着不少打好了
的鐵器。
LONG);
///    門口掛着一塊牌子(paizi)。
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"road11",
        ]));
        set("item_desc", ([
            "cannotsawpaizi" :
"若要'鑄劍'，請找歐冶師傅。\n"
"如果想在你的兵器上刻下帶色的字，可以在寶劍名\n"
"前面加上$XXX$，在寶劍名後記得恢復為$NOR$。\n"
"$BLK$ - 黑色            $NOR$ - 恢復正常顏色\n"
"$RED$ - 紅色            $HIR$ - 亮紅色\n"
"$GRN$ - 綠色            $HIG$ - 亮綠色\n"
"$YEL$ - 土黃色          $HIY$ - 黃色\n"
"$BLU$ - 深藍色          $HIB$ - 藍色\n"
"$MAG$ - 淺紫色          $HIM$ - 粉紅色\n"
"$CYN$ - 藍綠色          $HIC$ - 天青色\n"
"$WHT$ - 淺灰色          $HIW$ - 白色\n",
        ]));
        set("objects", ([ /* sizeof() == 1 */
//            __DIR__"npc/ouyezi" : 1,
            __DIR__"npc/smith" : 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "west")
        if( query_temp("marks/ouyezi", me) )
        {
           return notify_fail("鐵匠對你道：哎，這位客官，拿了兵器再走！\n");
        }
        return 1;
}