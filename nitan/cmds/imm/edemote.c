
#include <ansi.h>
#include <emotion.h>

inherit F_CLEAN_UP;

string help = @HELP
表情指令編輯器

edemote '表情指令'	- 編輯表情指令
edemote -d '表情指令'	- 刪除表情指令

HELP;


int help(object me) 
{
        write(help);
        return 1;
}
private int valid_emote_name(string emotion)
{
	return strsrch(emotion, " ") == -1;
}

private void choose_option(object me, string emotion, mapping modifying_emotion, string arg);
private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string contiune_arg, string arg);

private string replace_keys(string description)
{
	if( !description ) return "尚未設定";
	
	description = replace_string(description, "$ME", 	HIC"你"NOR);
	description = replace_string(description, "$YOU", 	HIG"某人"NOR);
	description = replace_string(description, "$T", 	HIM"事物"NOR);
	
	return description;
}
private string emotion_detail_description(string emotion, mixed info)
{
	string msg = "── 表情 "HIY+emotion+NOR+" 之詳細敍述如下："+repeat_string("─", 13-(strlen(emotion)/2))+"\n";
	
	msg += NOR WHT"1.無對象無附加文字    ："NOR+replace_keys(info[NONE_ALL])+"\n";
	msg += NOR WHT"2.無對象有附加文字    ："NOR+replace_keys(info[NONE_ALL_ARG])+"\n";
	msg += NOR WHT"3.對象為自己無附加文字："NOR+replace_keys(info[ME_ALL])+"\n";
	msg += NOR WHT"4.對象為自己有附加文字："NOR+replace_keys(info[ME_ALL_ARG])+"\n";
	msg += NOR WHT"5.對象為某人無附加文字："NOR+replace_keys(info[YOU_ALL])+"\n";
	msg += NOR WHT"6.對象為某人有附加文字："NOR+replace_keys(info[YOU_ALL_ARG])+"\n";
	msg += NOR WHT"7.表情註解            ："NOR+(info[NOTE] || "尚未設定")+"\n";
	msg += NOR WHT"8.使用次數            ："NOR+info[USE]+" 次\n";
	msg += "───────────────────────────\n";
	return msg;
}

private void confirm_delete_emotion(object me, string emotion, string arg)
{
	if( lower_case(arg) == "y" )
	{
		if( EMOTE_D->delete_emotion(emotion) )
			tell(me, "刪除表情指令 "+emotion+" 成功。\n");
		else
			tell(me, "刪除失敗，請通知巫師處理。\n");

		return me->finish_input();
	}
	else
	{
		tell(me, "取消刪除。\n");
		return me->finish_input();
	}
}

private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string multi_line_arg, string arg)
{
	if( !arg || !arg[0] )
	{
		multi_line_arg += "\n";
		tell(me, ">");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}
	
	switch(arg)
	{
		case "cancel":
			tell(me, "取消輸入敍述。\n"+emotion_detail_description(emotion, modifying_info)+"請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;
		
		case ".":
			// 最佳化敍述
			if(multi_line_arg[<1..] == "\n") multi_line_arg = multi_line_arg[0..<2];
			multi_line_arg = kill_repeat_ansi(trim(ansi(multi_line_arg)) + NOR);
			modifying_info[option-1] = multi_line_arg;
			
			tell(me, "設定完畢。\n"+emotion_detail_description(emotion, modifying_info)+"請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;
		default:
			multi_line_arg += arg+"\n";
			tell(me, ">");
			input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}
}
	
private void choose_option(object me, string emotion, mapping modifying_info, string arg)
{
	int option;
	
	switch(arg)
	{
		case "save":
			if( sizeof(modifying_info) != 8 )
			{
				tell(me, "必須設定完所有表情敍述才能儲存設定。\n請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
				input_to( (: choose_option, me, emotion, modifying_info :) );
				return;
			}
			else
			{
				array info = allocate(0);
				
				for(int i=0;i<8;i++)
					info += ({ modifying_info[i] });
					
				if( EMOTE_D->set_emotion(emotion, info) )
				{
					tell(me, "表情指令 "+emotion+" 設定儲存成功。\n");
				}
				else
					tell(me, "表情指令 "+emotion+" 設定儲存失敗。\n");
					
				return me->finish_input();
			}
			break;
			
		case "exit":
			tell(me, "取消對 "+emotion+" 表情指令的設定。\n");
			return me->finish_input();
			
		default:break;
	}
	
	option = to_int(arg);
	
	if( option > 8 || option < 1 )
	{
		tell(me, "沒有這個選項。\n請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else if( option == USE+1 ) 
	{
		tell(me, "這個選項無法使用手動設定。\n請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else
	{
		tell(me, "\n按 ENTER 可持續輸入多行，輸入 '.' 結束，輸入 'cancel' 取消。\n請輸入標準格式敍述 "HIC"$ME(代表自己) "HIG"$YOU(代表對象) "HIY"$T(代表附加文字)"NOR"：\n>");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, "" :) );
	}
}
	
int main(object me, string arg)
{
	string *info;
	mapping modifying_info = allocate_mapping(8);
	
        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;


	if( !arg ) { 
		tell(me, pnoun(2, me)+"想要增加或修改哪個表情指令？\n"); 
		return 1;
	}
	
	arg = remove_ansi(arg);
	
	if( sscanf(arg, "-d %s", arg) == 1 )
	{
		if( !arrayp(info = EMOTE_D->query_emotion(arg)) ) {
			tell(me, "沒有 "+arg+" 這個表情指令。\n");
			return 1;
		}
		
		tell(me, emotion_detail_description(arg, info)+"確定是否刪除 "+arg+" 表情指令(Yes/No)？");
		input_to( (: confirm_delete_emotion, me, arg :) );
		return 1;
	}
		
	if( arrayp(info = EMOTE_D->query_emotion(arg)) )
	{
		for(int i=0;i<8;i++)
			modifying_info[i] = info[i];
	}
	else
	{
		if( !valid_emote_name(arg) ) {
			tell(me, "不合法的表情指令名稱。\n");
			return 1;
		}
			
		modifying_info[NOTE] = 0;
		modifying_info[USE] = 0;
	}
		
	tell(me, emotion_detail_description(arg, modifying_info)+"請輸入欲設定之項目(設定完畢 save, 取消設定 exit)：\n>");
	input_to( (: choose_option, me, arg, modifying_info :) );
	return 1;
}
