// Room: /d/luoyang/lvzuan.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "呂祖庵");
        set("long",  @LONG
呂祖庵又叫呂祖廟，背依邙嶺坡，面臨深壑，壑內為清清流水。庵
紅垣綠槐琉璃房，小巧玲瓏，從崖下仰望，如見天空仙境。呂祖庵初為
茶庵，是行人飲茶歇腳之所。後改為道教場所。因庵中道人屬全真派，
故香火敬起全真派“五祖”之一的呂洞賓，因施茶性質未變，且廟宇規
模較小，故仍稱“呂祖庵”，亦稱“純陽洞”。 
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southwest" : __DIR__"mangshan",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6980);
	set("coor/y", 2280);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}