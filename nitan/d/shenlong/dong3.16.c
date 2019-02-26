inherit ROOM;

void create()
{
        set("short", "火焰洞外");
        set("long",@LONG
這是神龍島火焰洞外，據説洞內長滿各種毒蟲，傳説洞內住着一
只火焰巨獸，但是沒有人見過。
LONG);

	set("exits", ([
		"enter"   : __DIR__"huodong1",
		"west"   : __DIR__"dong3.15",

	]));

	// 未確保100%安全，在這裏也設置免死
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// 檢查是否已經開始麒麟戰鬥
        if (dir == "enter")
        {
                //return notify_fail("對不起，巫師還沒有下令開放，你暫時不能參加對抗火麒麟的戰鬥。\n");

        	ob = find_living("huo qilin");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/huodong1")
        		{
        			write("對不起，裏面已經開始了對抗火麒麟的戰鬥。\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"huodong1")))
        		env = load_object(__DIR__"huodong1");
        		
        	// 正在清場則不能進入
        	if( query("doing", env) )
       		{
       			write("火麒麟BOSS已經挑戰結束，正在等待清場，請稍後再試！\n");
       			return 0;
       		}
        }

        return 1;
}
