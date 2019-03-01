//  Room:  /d/lanzhou/jincheng.c

inherit  ROOM;

void  create  ()
{
        set("short",  "金城");
        set("long",  @LONG
金城郡設于西漢時，這裡是金城郡治所。金城渡口因其戰略位置的
重要性而聞名于世，歷史上許多著名的戰役就發生在這兒。
    河裡有幾只羊皮筏子(boat)，是用來擺渡的，喊一喊(yell)或許會
有人過來。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"road4",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3860);
	set("coor/z", 0);
	setup();
}

void init()
{
    add_action("do_yell", "yell");
}

int do_yell()
{
        return notify_fail("喊什麼喊，那邊還沒做好呢！\n");
}