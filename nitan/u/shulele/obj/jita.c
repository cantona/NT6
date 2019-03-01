// rose.c

#include <ansi.h>;
#include <command.h>;
inherit ITEM;

void create()
{
	set_name("電吉他", ({"dian jita", "jita"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long",@LONG
這是一把藍色的，很COOL的電吉他，上面系著幾根弦，彈（tan）
起來發出一陣美妙的韻律。
LONG
);
	set("value", 0);
	set_weight(10);
	}
	setup();
}
void init()
{
	add_action("do_tan", "tan");
}
int do_tan(string arg)
{
	object me = this_player();
	if( !arg || arg=="") return notify_fail("你要彈什麼？\n");
	
	if( me->query("qi") < 10 )
		return notify_fail("別再唱了，會沒命的！\n");
	if( arg == "jita"  || arg == "吉他"){
	   	message_vision("$N很COOL的拿起一把電吉他，激昂的音樂聲震撼著每一個少女的心懷。\n",me);
	   	me->add("qi",-10);
	   	me->set("title",HIR +"風"+ HIY +"總是"+ HIW +"吹過"NOR);
	switch( random(22) ) {
                case 0:
           	message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"Don~t Break My Heart，再次溫柔，喜悅總是出現在我夢中～～\n"NOR,users());
		break;
                case 1:
                message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我的熱情，好象一把火，燃燒了整個沙漠，太陽見了我，也會躲著我～～\n"NOR,users());
		break;
                case 2:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我承認都是月亮惹的禍，那樣的夜色太美你太溫柔～～\n"NOR,users());
		break;
        	case 4:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"都是你的錯，輕易愛上我，讓我不知不覺滿足被愛的虛榮～～\n"NOR,users());
		break;
		case 5:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"今夜的寒風將我心撕碎，悵慌的腳步我不醉不歸，朦朧的細雨有朦朧的美～～\n"NOR,users());
		break;
	 	case 6:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我怎麼哭得如此狼狽，是否我對你還有所依戀～～\n"NOR,users());
		break;
	   	case 7:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"一杯酒，二角銀，三句告心嘛來湊陣～～\n"NOR,users());
		break;
	   	case 8:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"冷冷的冰雨在臉上胡亂的拍，冷冷的眼淚跟雨水混成一塊～～\n"NOR,users());
		break;
	   	case 9:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我想哭但是哭不出來，跟著～～\n"NOR,users());
		break;
		case 10:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"說了是無心，做了更無情，都說做無情人有何必再寫信～～\n"NOR,users());
		break;
		case 11:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"情花開，開燦爛，快樂永無限～～\n"NOR,users());
		break;
		case 12:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"當年相戀意中人，大家性情近，空有愛絲萬千丈，早經消散化煙雲～～\n"NOR,users());
		break;
		case 13:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"來吧我什麼都應承，來吧我什麼都聽命～～\n"NOR,users());
		break;
		case 14:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"冷雨夜我不想歸家，盼望你背影，可苦笑望雨點，雖知要說清楚，可惜我沒膽試～～\n"NOR,users());
		break;
		case 15:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我會搽去我不小心滴下的淚水，還會裝做一切都無所謂～～\n"NOR,users());
		break;
		case 16:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"讓我將你心兒摘下，試著讓它漫漫融化，看我在你心中是否仍完美□瑕～～\n"NOR,users());
		break;
		case 17:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"當他對你說一往情深，你千萬不要信以為真，不要輕易的付出你的吻～～\n"NOR,users());
		break;
		case 18:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"哦相思無用，哦相思無用，對我是一種太昂貴的痛～～\n"NOR,users());
		break;
		case 19:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"Every Sha La La La，Every How How，Sunshine～～\n"NOR,users());
		break;
		case 20:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"我的愛如潮水，愛如潮水將我向你推，緊緊跟隨，愛如潮水它將你我包圍～～\n"NOR,users());
		break;
		case 21:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"今天晚上的星星很少，不知道它們到哪裡了～～\n"NOR,users());
		break;
		case 22:
		message("channel:chat",HIY"□"+me->query("name")+"笑傲江湖演唱會□："HIC"哎喲向著天空拜拜呀勇敢站起來，老天愛笨小孩。\n"NOR,users());
		break;
		}
	return 1;
	}
}
