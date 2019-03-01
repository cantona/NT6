// zhandao.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "長空棧道");
        set("long", @LONG
棧道以鐵斜插，上覆青石板，寬不足八寸。上乃絕壁，下亦絕壁。
挽索登其上，只聽山風呼嘯，林濤怒吼。遠處偶傳一兩聲禽鳴獸嘶，
更使人毛骨悚然。踏上懸空的棧道，緊攀鐵索，屏息靜氣，緩步挪動，
才能過去。
LONG );
        set("exits", ([ /* sizeof() == 4 */
           "southup"   : __DIR__"luoyan",
           "northdown" : __DIR__"sgyhole",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}