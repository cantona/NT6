// Room: /chengdu/tidufu.c
// Date: Feb.14 1998
inherit ROOM;

void create()
{
        set("short", "提督府");
        set("long", @LONG
這裏便是提督大人辦公事的地方。正前方 (front)大紅楠木案桌
後正經端坐着的，就是成都提督吳天德。兩邊站立紋絲不動的是他的
親兵侍從，看上去都十分彪悍。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"tidugate",
        ]));
        set("objects", ([ /* sizeof() == 1 */
             __DIR__"npc/wutiande" : 1,
             __DIR__"npc/shicong"  : 2,
             __DIR__"npc/qinbing" : 4,
        ]));
        set("item_desc",([
            "front" : "
                ###########################
                #                         #
                #    民   安   境   靖    #
                #                         #
                ###########################
                            !~A~!
                      @~~~~~!(O)!~~~~~@
                           (.@ @.)
                            . ~ .
                         /   ~.你奶奶的...你這刁民...還瞧甚麼? 不認得老爺麼? ...
                        #           #
             HHHH     #               #
             HHHH   #    n         n    #
          |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
           ```````````````````````````````````````
                  ()                      ()
                 ()                        ()
                ()                          ()
               ()                            ()\n"
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}