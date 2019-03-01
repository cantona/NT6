//houyuan.c

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/連城訣/"
#define QUESTDIR1 "quest/連城訣/雪谷激鬥篇/"
#define QUESTDIR2 "quest/連城訣/武館探密篇/"

void create()
{
        set("short", "後院");
        set("long", @LONG
這裡落腳似乎是一個大院了，四周堆滿了雜物，似乎很久沒有人來，遠遠
望去是館主冬暖閣的窗口。只是四周牆壁似乎有些奇怪。東面牆總感覺像新砌
的一樣；西面牆確是下面一小半陷落，似乎可以從洞口鑽過去。
LONG
    );
        setup();
}
void init()
{
	add_action("do_jump", ({"jump", "tiao"}));
	add_action("do_enter", ({"zuan"}));
	add_action("do_wa", ({"wa"}));
}
int do_jump(string arg)
{
	object room,me = this_player();
    if( arg == "chuang" || arg == "window" || arg == "chuanghu" || arg == "chuangkou")
    {
		if(me->query_skill("dodge")<100) 
		{
			message_vision(HIY"\n$N吸了一口氣，想從窗口跳出去。\n"NOR,me);
			return notify_fail("萬震山上前把手一伸：這位"+RANK_D->query_respect(me) +"，你要幹什麼？！");
		}
		if (!(room = find_object(__DIR__"woshi")))
			room = load_object(__DIR__"woshi");
		if(!room)
		{ 
			tell_object(me,HIR"\n你無論怎麼跳，發現都還在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少woshi.c文件。\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N吸了一口氣，乘萬震山不注意，突然直接從窗口跳了進去。\n"NOR, me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\n只見一個身影飛身而過，原來是"+me->name()+"從窗戶下跳了進來。\n"NOR, ({me}));                       	
		}
		return 1;
	}
	return 0;
}
int do_enter(string arg)
{
	object room,me = this_player();
    if( arg == "dong" )
    {
		if (!(room = find_object(__DIR__"citang")))
			room = load_object(__DIR__"citang");
		if(!room)
		{ 
			tell_object(me,HIR"\n你無論怎麼鑽，發現都還在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少citang.c文件。\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N慢慢探下身來，從洞口爬了進去。\n"NOR, me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\n只見一個人叢一個角落爬了出來，原來是"+me->name()+"。\n"NOR, ({me}));                       	
		}
		return 1;
	}
	return 0;
}
int do_wa(string arg)
{
	object me = this_player();
	if(!arg || arg!="qiang") 
		return notify_fail("你要挖什麼？\n");
	if(!present("gao tou",me))
		return notify_fail("沒有鎬頭，怎麼挖牆？\n");
	if(!me->query_temp(QUESTDIR2+"askqiqiang" ))
		return notify_fail("無緣無故，你挖牆幹什麼？\n");
	if(!me->query_temp(QUESTDIR2+"askwan_diyun" ))
		return notify_fail("無緣無故，你挖牆幹什麼？\n");
	if(!me->query_temp(QUESTDIR2+"askwan_qi" ))
		return notify_fail("無緣無故，你挖牆幹什麼？\n");
	if(me->query_temp(QUESTDIR2+"waqiang" ))
		return notify_fail("你已經發現這裡的秘密了。\n");
	if(me->is_busy())
		return notify_fail("你正累著呢。\n");
	if(me->query_temp(QUESTDIR2+"wa_qiang_ing" )<=5)
	{
        message_vision(HIC"\n$N將牆洞用力堆了幾下，又掄起鎬頭將牆扒了一扒。\n"NOR, me);
		tell_object(me,RED"一會兒，你就累得滿頭大汗！\n"NOR);
		me->start_busy(3);
		me->add_temp(QUESTDIR2+"wa_qiang_ing",1);
		return 1;
	}
	message_vision(HIY"\n$N將牆洞用力堆了幾下，然後掄起鎬頭將牆扒了開來。\n"NOR, me);
	message_vision(HBYEL"\n$N竟然發現牆壁竟然內有中空。\n"NOR, me);
	tell_object(me,CYN"\n看來，破祠堂的中年乞婦所說沒錯。萬震山害死戚長發，嫁禍狄雲。\n"NOR);
	tell_object(me,CYN"只是，連城訣的秘密究竟在什麼地方呢？\n"NOR);
	me->start_busy(1);
	me->set_temp(QUESTDIR2+"waqiang",1);
	return 1;	
}

