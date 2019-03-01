// Room: /u/zqb/tiezhang/bqshi.c

inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
鐵掌幫雖是以掌法、輕功著稱，但幫中仍存有大量的兵器。以供武功不
夠的幫眾使用。屋內兩側排列的都是兵器架，上面刀、槍、劍、戟、斧、鉞
鉤、叉應有盡有。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"zoulang-1",
]));
    set("objects", ([ /* sizeof() == 4 */
  __DIR__"obj/gangdao" : 1,
  __DIR__"obj/gangjian" : 1,
  __DIR__"obj/gangzhang" : 1,
  __DIR__"obj/changbian" : 1,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}