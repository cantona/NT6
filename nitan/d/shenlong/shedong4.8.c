inherit ROOM;

void create()
{
        set("short", "蛇精洞外");
        set("long",@LONG
這是蛇精洞外，再往前走就要進入蛇精洞了，據說，還沒有人能活著
走出蛇精洞。
LONG);


	set("exits", ([
		"north"  : __DIR__"shedong4.7",		
		"enter"   : __DIR__"shejingdong",
	]));

	// 為確保100%安全，這裡也設置免死
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// 檢查是否已經開始蛇精戰鬥
        if (dir == "enter")
        {
                //return notify_fail("對不起，巫師還沒有下令開放，你暫時不能參加對抗蛇精的戰鬥。\n");
        	
        	ob = find_living("jiutou shejing");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
        		{
        			write("對不起，裡面已經開始了對抗蛇精的戰鬥。\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"shejingdong")))
        		env = load_object(__DIR__"shejingdong");
        		
        	// 正在清場則不能進入
        	if( query("doing", env) )
       		{
       			write("蛇精BOSS已經挑戰結束，正在等待清場，請稍後再試！\n");
       			return 0;
       		}
        	
        }

        return 1;
}
