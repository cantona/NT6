/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : baseball.c
 * Author : Clode@RevivalWorld
 * Date   : 2009-08-10
 * Note   : 棒球指令
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <feature.h>
#include <daemon.h>
#include <message.h>
#include <baseball.h>
#include <time.h>

inherit F_CLEAN_UP;

#define RECORD_SIZE 	30

string help = @HELP
   棒球指令，可以查詢棒球比賽相關資訊

   baseball			- 顯示目前參賽隊伍、戰況、球隊基本資訊
   
   baseball info		- 查詢自己所屬球員紀錄
   baseball info '玩家ID'	- 查詢其他玩家球員紀錄
   
   baseball listen '玩家ID'	- 收聽某位玩家的球隊比賽實況
   baseball listen -d		- 停止收聽比賽實況
   
   baseball record '種類'	- 查詢球員紀錄排行(種類包括 home, hit, hit2, hit3, run, k, era, special)
   baseball record '種類' 年度	- 查詢球員紀錄排行(某一特定年度)

   baseball hint '暗號'		- 下達暗號，每場球賽最多使用 6 次暗號
   	
   暗號種類如下 : 	
   batter 	- 鼓舞目前場上打者，讓他在這次上場機會中短暫提升打擊威力
   pitcher 	- 鼓舞目前場上投手，讓他與目前打者的對決中短暫提升投球威力
   bunt		- 打暗號給場上打者，要求其進行觸擊短打，以掩護壘上跑者推進(不計入暗號次數)
   walk		- 打暗號給場上投手，要求其敬遠四壞保送目前打者(不計入暗號次數)
HELP;

int main(object me, string arg)
{
	string value;
	int year = BASEBALL_D->query_season_year();
	string myid = me->query_id(1);
	string *msg = allocate(0);
	
	if( !arg )
	{
		string *season = BASEBALL_D->query_season();
		mapping setup = BASEBALL_D->query_setup();
		mapping record = BASEBALL_D->query_record();
		
		int win, lose;
		int sep = 0;
		string opponent;
		string statustext;
		int rank = 0;
		int limit;
		
		msg = ({ "\n 第 "HIC+year+NOR" 球季目前共有 "HIY+sizeof(season)+NOR" 個參賽球隊，目前戰績排名如下：" });
		msg += ({ WHT"─────────────────────────────────────"NOR });
		msg += ({ sprintf(HIW" %-4s%-13s%-13s%4s%5s%5s%6s %-12s%s"NOR, "", "球隊名稱", "老闆", "場次", "勝場", "敗場", "勝率", "目前對戰", "賽況") });
		msg += ({ WHT"─────────────────────────────────────"NOR });
		
		limit = (BASEBALL_D->calculate_max_game_times(year)-10) / 2;
		
		if( limit < 10 ) limit = 10;
			
		foreach(string id in sort_array(season, (: BASEBALL_D->sort_team($1, $2) :) ))
		{
			if( mapp(record[year]) && mapp(record[year][RECORD_TEAM][id]) )
			{
				win = record[year][RECORD_TEAM][id]["win"];
				lose = record[year][RECORD_TEAM][id]["lose"];
			}
			else
			{
				win = 0;
				lose = 0;
			}
			
			if( !mapp(setup[id]) ) continue;
				
			if( win+lose < limit && sep == 0 )
			{
				msg += ({ WHT"───────────── "NOR"場次數量條件不足"WHT" ───────────────"NOR });
				sep = 1;
			}
			
			if( rank == 8 )
				msg += ({ NOR RED"────────────── "HIR"季後賽晉級條件"NOR RED" ───────────────"NOR });
			
			//else if( rank == 12 )
			//	msg += ({ NOR RED"────────────── "HIR"季後賽晉級條件"NOR RED" ───────────────"NOR });
			
			opponent = BASEBALL_D->query_opponent(id);
			
			switch(BASEBALL_D->query_status(id))
			{
				case STATUS_IDLE:
				{
					if( BASEBALL_D->is_in_post_season() )
					{
						if( member_array(id, BASEBALL_D->query_post_season_eliminate_teams()) != -1 )
							statustext = RED"淘汰"NOR;
						else if( member_array(id, BASEBALL_D->query_post_season_team(2)) != -1 )
							statustext = HIY"晉級"NOR YEL"總冠軍賽"NOR;		
						else if( member_array(id, BASEBALL_D->query_post_season_team(4)) != -1 )
							statustext = HIG"晉級"NOR GRN"四強賽"NOR;
						else if( member_array(id, BASEBALL_D->query_post_season_team(8)) != -1 )
							statustext = HIC"晉級"NOR CYN"八強賽"NOR;
						else
							statustext = WHT"休賽"NOR;
					}
					else
						statustext = HIG"配"NOR GRN"對中"NOR;
					break;
				}
				case STATUS_PLAYING:
				{
					mapping game = BASEBALL_D->query_game(id);
						
					if( id == game[TEAM1] )
						statustext = sprintf(CYN"%-2d"NOR":"HIC"%2d"NOR, game[TEAM2SCORE], game[TEAM1SCORE]);
					else
						statustext = sprintf(HIC"%-2d"NOR":"CYN"%2d"NOR, game[TEAM2SCORE], game[TEAM1SCORE]);
						   
					statustext += sprintf(" "WHT"%s"HIW"%d"NOR, (game[INNING]%2?"↑":"↓"), (game[INNING]/2+game[INNING]%2));
					break;	
				}
				case STATUS_PREPARING:
				{
					mapping game = BASEBALL_D->query_game(id);
					statustext = HIY"準"NOR YEL"備中"NOR+" "+HIY+((PREPARETIME - game[TICK])/60+1)+NOR YEL+"m"NOR;
					break;	
				}
			}
			msg += ({ sprintf(" %-4s%-13s"HIC"%-13s"HIW"%4d"HIR"%5d"HIG"%5d"HIY+(win>0&&lose==0?"%6.1f":"%6.2f")+NOR CYN" %-12s"NOR"%s", sep == 0 ? to_string(++rank):"", setup[id]["name"], capitalize(id), win+lose, win, lose, lose+win > 0. ? (win*100./(lose+win)) : 0., opponent ? capitalize(opponent) : "", statustext) });
		}
		
		msg += ({ WHT"─────────────────────────────────────"NOR });
		
		if( !undefinedp(setup[myid]) )
		{
			if( setup[myid]["keepwins"] > 1 )
				msg += ({ pnoun(2, me)+"的球隊最近打出 "HIR+setup[myid]["keepwins"]+NOR" 連勝，士氣高昂" });
			if( setup[myid]["keeploses"] > 1 )
				msg += ({ pnoun(2, me)+"的球隊最近苦吞 "HIG+setup[myid]["keeploses"]+NOR" 連敗，士氣低落" });
		}

		if( BASEBALL_D->is_in_post_season() )
			msg += ({ " 目前正在進行第 "HIC+year+NOR" 球季季後賽" });
		else 
		{
			int eta = 1282456800 + 604800*year - time();
			
			if( eta < 0 )
				msg += ({ " 第 "HIC+year+NOR" 球季季後賽準備中"NOR });
			else
				msg += ({ " 距離第 "HIC+year+NOR" 球季季後賽還有 "HIY+(eta/60/60/24)+" 天 "+(eta/60/60%24)+" 小時 "+(eta/60%60)+" 分"NOR });
		}
			
		msg += ({ " 查詢球員排行紀錄 / 收聽各球隊即時戰況 / 下達暗號 - help baseball" });
		msg += ({ WHT"─────────────────────────────────────"NOR });
		return tell(me, implode(msg, "\n")+"\n");
	}
	else if( sscanf(arg, "record %s", value) == 1 )
	{
		string *recordsort;
		mapping record = BASEBALL_D->query_record();
		mapping playerrecord;
		int count;
		
		object labor;
		
		sscanf(value, "%s %d", value, year);
		
		if( !mapp(record[year]) )
			return tell(me, "並沒有第 "+year+" 球季的紀錄。\n");
			
		playerrecord = record[year][RECORD_PLAYER];
			
		msg += ({ " 第 "HIC+year+NOR" 球季所有球員紀錄排名如下：" });
		
		switch(lower_case(value))
		{
			case "home":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 全壘打王                    球隊老闆      支數"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["hit4"] > 0 :)), (: $(playerrecord)[$1]["hit4"] > $(playerrecord)[$2]["hit4"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["hit4"]) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "hit":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 安打王                      球隊老闆      支數       打擊率"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["hit"] > 0 :)), (: $(playerrecord)[$1]["hit"] > $(playerrecord)[$2]["hit"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"HIY"%13.2f"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["hit"], 10.*playerrecord[file]["hit"]/playerrecord[file]["ab"]) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "hit2":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 二壘安打王                  球隊老闆      支數       打擊率"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["hit2"] > 0 :)), (: $(playerrecord)[$1]["hit2"] > $(playerrecord)[$2]["hit2"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"HIY"%13.2f"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["hit2"], 10.*playerrecord[file]["hit2"]/playerrecord[file]["ab"]) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "hit3":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 三壘安打王                  球隊老闆      支數       打擊率"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["hit3"] > 0 :)), (: $(playerrecord)[$1]["hit3"] > $(playerrecord)[$2]["hit3"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"HIY"%13.2f"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["hit3"], 10.*playerrecord[file]["hit3"]/playerrecord[file]["ab"]) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "run":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 打點王                      球隊老闆      打點"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["rbi"] > 0 :)), (: $(playerrecord)[$1]["rbi"] > $(playerrecord)[$2]["rbi"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["rbi"]) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "k":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 三振王                      球隊老闆      三振       三振率"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["strikeout"] > 0 :)), (: $(playerrecord)[$1]["strikeout"] > $(playerrecord)[$2]["strikeout"] ? -1 : 1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"HIY"%12.2f%%"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["strikeout"], playerrecord[file]["bf"]>0?100.*playerrecord[file]["strikeout"]/playerrecord[file]["bf"]:0.) });
					
					if( --count == 0 ) break;
				}
				
				break;
			}
			case "era":
			{
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 排名 防禦率王                    球隊老闆       局數(>45)     自責分率"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });
				
				recordsort = sort_array( filter_array(keys(playerrecord), (: $(playerrecord)[$1]["out"] > 135 :)), (: to_float($(playerrecord)[$1]["run"])/$(playerrecord)[$1]["out"] > to_float($(playerrecord)[$2]["run"])/$(playerrecord)[$2]["out"] ? 1 : -1 :) );
					
				count = RECORD_SIZE;
				foreach(string file in recordsort)
				{
					if( !file_exists(file) ) continue;
						
					labor = load_object(file);
					
					if( !query("boss", labor) ) continue;
						
					msg += ({ sprintf(" "HIW"%-5d"NOR"%-28s"HIC"%-12s"HIY"%6d"HIY"%19.2f"NOR, RECORD_SIZE+1-count, labor->query_idname(), capitalize(query("boss", labor)), playerrecord[file]["out"]/3, playerrecord[file]["out"]>0?27.*playerrecord[file]["run"]/playerrecord[file]["out"]:0.) });
					
					if( --count == 0 ) break;
				}
		
				break;
			}
			case "special":
			{
				mapping specialrecord = record[year][RECORD_SPECIAL];
				
				msg += ({ WHT"─────────────────────────────────────"NOR });
				msg += ({ HIW" 特殊紀錄             紀錄   達成隊伍 / 球員               老闆"NOR });
				msg += ({ WHT"─────────────────────────────────────"NOR });

				if( stringp(specialrecord["champion"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["champion"]);
					msg += ({ sprintf(NOR YEL" 球季總冠軍                  %-30s"HIC"%s"NOR, mapp(setup) ? setup["name"] : specialrecord["champion"], capitalize(specialrecord["champion"])) });
				}
				
				if( stringp(specialrecord["2rd"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["2rd"]);
					msg += ({ sprintf(NOR YEL" 球季亞軍                    %-30s"HIC"%s"NOR, mapp(setup) ? setup["name"] : specialrecord["2rd"], capitalize(specialrecord["2rd"])) });
					msg += ({ "" });
				}
				
				if( stringp(specialrecord["keepwinsteam"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["keepwinsteam"]);
					msg += ({ sprintf(NOR YEL" 最長連勝場次        "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["keepwins"], mapp(setup) ? setup["name"] : specialrecord["keepwinsteam"], capitalize(specialrecord["keepwinsteam"])) });
				}
				
				if( stringp(specialrecord["keeplosesteam"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["keeplosesteam"]);
					msg += ({ sprintf(NOR YEL" 最長連敗場次        "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["keeploses"], mapp(setup) ? setup["name"] : specialrecord["keeplosesteam"], capitalize(specialrecord["keeplosesteam"])) });
				}
				
				if( stringp(specialrecord["maxstrikeoutsplayer"]) )
				{
					object player;
					
					if( file_exists(specialrecord["maxstrikeoutsplayer"]) )
						player = load_object(specialrecord["maxstrikeoutsplayer"]);
						
					msg += ({ sprintf(NOR YEL" 單場最多三振次數    "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxstrikeouts"], objectp(player) ? player->query_idname() : "已消失", objectp(player) ? capitalize(query("boss", player)) : "") });
				}
				if( stringp(specialrecord["maxhomerundistanceplayer"]) )
				{
					object player;
					
					if( file_exists(specialrecord["maxhomerundistanceplayer"]) )
						player = load_object(specialrecord["maxhomerundistanceplayer"]);
						
					msg += ({ sprintf(NOR YEL" 全壘打最長距離      "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxhomerundistance"], objectp(player) ? player->query_idname() : "已消失", objectp(player) ? capitalize(query("boss", player)) : "") });
				}
				if( stringp(specialrecord["maxhitsteam"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["maxhitsteam"]);
					msg += ({ sprintf(NOR YEL" 單場最多安打數      "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxhits"], mapp(setup) ? setup["name"] : specialrecord["maxhitsteam"], capitalize(specialrecord["maxhitsteam"])) });
				}
				
				if( stringp(specialrecord["maxscoresteam"]) )
				{
					mapping setup = BASEBALL_D->query_setup(specialrecord["maxscoresteam"]);
					msg += ({ sprintf(NOR YEL" 單場最多得分數      "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxscores"], mapp(setup) ? setup["name"] : specialrecord["maxscoresteam"], capitalize(specialrecord["maxscoresteam"])) });
				}

				if( stringp(specialrecord["maxinningsteam1"]) && stringp(specialrecord["maxinningsteam2"]) )
				{
					msg += ({ sprintf(NOR YEL" 延長賽最長局數      "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxinnings"]/2+specialrecord["maxinnings"]%2, (mapp(BASEBALL_D->query_setup(specialrecord["maxinningsteam1"])) ? BASEBALL_D->query_setup(specialrecord["maxinningsteam1"])["name"] : specialrecord["maxinningsteam1"])+" & "+(mapp(BASEBALL_D->query_setup(specialrecord["maxinningsteam2"])) ? BASEBALL_D->query_setup(specialrecord["maxinningsteam2"])["name"] : specialrecord["maxinningsteam2"]), capitalize(specialrecord["maxinningsteam1"]) +" & "+capitalize(specialrecord["maxinningsteam2"])) });
				}
				
				if( stringp(specialrecord["maxscorediffwin"]) && stringp(specialrecord["maxscoredifflose"]) )
				{
					msg += ({ sprintf(NOR YEL" 單場分數最大差距    "HIY"%5d"NOR"   %-30s"HIC"%s"NOR, specialrecord["maxscorediff"], (mapp(BASEBALL_D->query_setup(specialrecord["maxscorediffwin"])) ? BASEBALL_D->query_setup(specialrecord["maxscorediffwin"])["name"] : specialrecord["maxscorediffwin"])+" & "+(mapp(BASEBALL_D->query_setup(specialrecord["maxscoredifflose"])) ? BASEBALL_D->query_setup(specialrecord["maxscoredifflose"])["name"] : specialrecord["maxscoredifflose"]), capitalize(specialrecord["maxscorediffwin"]) +" & "+capitalize(specialrecord["maxscoredifflose"])) });
				}
				break;
			}
			default:
				return tell(me, "請輸出正確的紀錄種類(home, hit, hit2, hit3, run, k, era, special)。\n");
		}
		msg += ({ WHT"─────────────────────────────────────"NOR });
		
		return me->more(implode(msg, "\n")+"\n");
	}
	else if( arg == "info" || sscanf(arg, "info %s", value) == 1 )
	{
		string target;
		mapping setup;
		string text;
		object labor;
		string position;
		string file;
		int win;
		int lose;
		int out, bf, run, strikeout;
		int handside = HANDSIDE_NONE;
		string handsidename;
		
		if( value )
			target = value;
		else
			target = myid;
			
		if( !BASEBALL_D->exists(target) )
			return tell(me, "沒有 "+target+" 這位玩家，或該玩家並未建立球隊。\n");

		setup = BASEBALL_D->query_setup(target);

		text = (target == myid ? pnoun(2, me) : find_player(target) ? find_player(target)->query_idname() : capitalize(target)+" ")+"的球隊名稱為“"+(setup["name"]||"未命名")+"”隊，目前安排的球員守備位置與打擊棒次資料如下：\n";
		
		text += WHT"─────────────────────────────────────\n"NOR;
		text += sprintf(HIW"%-4s %-9s%5s%5s%5s%5s%10s%10s %s\n"NOR, "", "守備位置", "自責", "局數", "四壞", "三振", "三振率", "方向", "球員名稱" );
		text += WHT"─────────────────────────────────────\n"NOR;
		
		labor = 0;
		position = 0;

		if( mapp(setup["roster"][0]) )
		{
			file = setup["roster"][0]["file"];
			
			if( file_exists(file) )
				labor = load_object(file);

			handside = BASEBALL_D->get_handside_type(labor);
			position = BASEBALL_D->query_positionname(setup["roster"][0]["position"]);
		}

		switch(handside)
		{
			case HANDSIDE_NONE: handsidename = ""; break;
			case HANDSIDE_LEFTHAND: handsidename = HIC"左"NOR CYN"投"NOR; break;
			case HANDSIDE_RIGHTHAND: handsidename = HIG"右"NOR GRN"投"NOR; break;
			case HANDSIDE_TWOHANDS: handsidename = "錯誤"; break;
		}
		
		out = BASEBALL_D->get_record(RECORD_PLAYER, file, "out", year);
		bf = BASEBALL_D->get_record(RECORD_PLAYER, file, "bf", year);
		run = BASEBALL_D->get_record(RECORD_PLAYER, file, "run", year);
		strikeout = BASEBALL_D->get_record(RECORD_PLAYER, file, "strikeout", year);
		
		text += sprintf(" %-3s %-9s"HIG"%5.2f"HIC"%5d"HIM"%5d"HIY"%5d"HIY"%9.2f%%"NOR"%10s %s\n", 
			"",
			position || WHT"未設定"NOR, 
			out > 0 ? run * 9. / (out / 3.): 0.,
			out / 3,
			BASEBALL_D->get_record(RECORD_PLAYER, file, "fourball", year),
			strikeout,
			bf > 0 ? 100. * strikeout / bf : 0.,
			handsidename,
			objectp(labor) ? labor->query_idname() : WHT"未設定"NOR
		);
			
		text += WHT"\n"NOR;
		text += sprintf(HIW"%-4s %-9s%5s%5s%5s%5s%5s%5s%5s%5s %s\n"NOR, "棒次", "守備位置", "打率", "安打", "二安", "三安", "全壘", "打點", "保送", "方向", "球員名稱");
		text += WHT"─────────────────────────────────────\n"NOR;
		
		for(int i=1;i<10;++i)
		{
			labor = 0;
			position = 0;
			handside = HANDSIDE_NONE;
			
			if( mapp(setup["roster"][i]) )
			{
				file = setup["roster"][i]["file"];
				
				if( file_exists(file) )
					labor = load_object(file);

				handside = BASEBALL_D->get_handside_type(labor);
				position = BASEBALL_D->query_positionname(setup["roster"][i]["position"]);
			}

			switch(handside)
			{
				case HANDSIDE_NONE: handsidename = ""; break;
				case HANDSIDE_LEFTHAND: handsidename = HIC"左"NOR CYN"打"NOR; break;
				case HANDSIDE_RIGHTHAND: handsidename =HIG"右"NOR GRN"打"NOR; break;
				case HANDSIDE_TWOHANDS: handsidename = HIY"左"NOR YEL"右"NOR; break;
			}
		
			text += sprintf(" %-3s %-9s"HIG"%5.2f"HIC"%5d"HIY"%5d"HIY"%5d"HIY"%5d"HIW"%5d"HIM"%5d"NOR" %4s %s\n", 
				HIG+i+NOR, 
				position || WHT"未設定"NOR, 
				BASEBALL_D->get_hit_rate(target, i, year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "hit", year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "hit2", year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "hit3", year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "hit4", year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "rbi", year),
				BASEBALL_D->get_record(RECORD_PLAYER, file, "walk", year),
				handsidename,
				objectp(labor) ? labor->query_idname() : WHT"未設定"NOR
			);
		}
	
		text += WHT"─────────────────────────────────────\n"NOR;
		for(int y=year;y>=1;--y)
		{
			win = BASEBALL_D->get_record(RECORD_TEAM, target, "win", y);
			lose = BASEBALL_D->get_record(RECORD_TEAM, target, "lose", y);
		
			text += WHT"第 "HIW+y+NOR WHT" 球季"NOR"季賽勝場數："HIR+win+NOR" / 敗場數："HIG+lose+NOR" / 勝率："HIY+sprintf("%.2f", win+lose > 0 ? 100.*win/(win+lose) : 0.)+NOR YEL"%"NOR"\n";
		}
		text += WHT"─────────────────────────────────────\n"NOR;
		me->more(text);
		
		return;
	}
	else if( sscanf(arg, "listen %s", arg) == 1 )
	{
		if( arg == "-d" )
		{
			BASEBALL_D->set_listener(myid, 0);
			return tell(me, pnoun(2, me)+"停止收聽所有比賽實況。\n");
		}
		
		if( !arg || !arg[0] )
			return tell(me, "請輸入正確的指令格式。\n");

		if( !BASEBALL_D->in_season(arg) )
			return tell(me, arg+" 並沒有球隊加入季賽。\n");
			
		BASEBALL_D->set_listener(myid, arg);
		
		return tell(me, pnoun(2, me)+"開始收聽 "+arg+" 的球隊比賽實況。\n");
	}
	else if( sscanf(arg, "hint %s", arg) == 1 )
	{
		string *signals = ({ NOR WHT"|"HIW"o"NOR WHT"|"NOR, NOR WHT"\\"HIW"o"NOR WHT"\\"NOR, NOR WHT"/"HIW"o"NOR WHT"/"NOR, NOR WHT"\\"HIW"o"NOR WHT"/"NOR, NOR WHT"-"HIW"o"NOR WHT"-"NOR  });
		string signal;
		mapping setup;
		mapping game;
		
		if( BASEBALL_D->query_status(myid) != STATUS_PLAYING )
			return tell(me, pnoun(2, me)+"的球隊目前並未進行球賽。\n");
		
		setup = BASEBALL_D->query_setup(myid);
				
		if( setup["hint"] > 0 )
			return tell(me, pnoun(2, me)+"前一次下達的暗號目前仍然有效，無法重覆下達暗號。\n");

		game = BASEBALL_D->query_game(myid);
		
		signal = signals[random(5)]+"  "+signals[random(5)]+"  "+signals[random(5)];

		switch(arg)
		{
			case "batter":
				
				if( setup["hinttimes"] <= 0 ) 
					return tell(me, pnoun(2, me)+"這次球賽的暗號下達次數已達上限。\n");
			
				if( ((game[INNING]%2) > 0 && game[TEAM2] == myid) || ((game[INNING]%2) == 0 && game[TEAM1] == myid) )
				{
					tell(me, pnoun(2, me)+"下達暗號鼓舞正在打擊的打者，這一輪打席的打擊威力短暫提升。\n");
					BASEBALL_D->add_message(myid, me->query_idname()+"緊張地對着打者比了三個連打者都看不太懂的手勢“ "+signal+" ”");
					setup["hint"] = HINTTYPE_BATTER;
					
					setup["hinttimes"]--;
				}
				else
					return tell(me, "目前"+pnoun(2, me)+"是防守方，無法對打者下達暗號。\n");

				break;
			case "bunt":
				if( (game[INNING]%2) > 0 && game[TEAM2] == myid || ((game[INNING]%2) == 0 && game[TEAM1] == myid) )
				{
					tell(me, pnoun(2, me)+"下達暗號給正在打擊的打者，要求其進行觸擊短打以掩護壘上跑者推進。\n");
					BASEBALL_D->add_message(myid, me->query_idname()+"緊張地對着打者比了三個連打者都看不太懂的手勢“ "+signal+" ”");
					setup["hint"] = HINTTYPE_BUNT;
				}
				else
					return tell(me, "目前"+pnoun(2, me)+"是防守方，無法對打者下達暗號。\n");
					
				break;
			case "pitcher":
				
				if( setup["hinttimes"] <= 0 ) 
					return tell(me, pnoun(2, me)+"這次球賽的暗號下達次數已達上限。\n");
			
				if( (game[INNING]%2) == 0 && game[TEAM2] == myid || ((game[INNING]%2) > 0 && game[TEAM1] == myid) )
				{
					tell(me, pnoun(2, me)+"下達暗號鼓舞正在投球的投手，面對目前打者的投球威力短暫提升。\n");
					BASEBALL_D->add_message(myid, me->query_idname()+"緊張地對着投手比了三個連投手都看不太懂的手勢“ "+signal+" ”");
					setup["hint"] = HINTTYPE_PITCHER;
					
					setup["hinttimes"]--;
				}
				else
					return tell(me, "目前"+pnoun(2, me)+"是攻擊方，無法對投手下達暗號。\n");
					
				break;
			case "walk":
				if( (game[INNING]%2) == 0 && game[TEAM2] == myid || ((game[INNING]%2) > 0 && game[TEAM1] == myid) )
				{
					tell(me, pnoun(2, me)+"下達暗號鼓舞正在投球的投手，要求其敬遠四壞保送目前打者。\n");
					BASEBALL_D->add_message(myid, me->query_idname()+"緊張地對着投手比了三個連投手都看不太懂的手勢“ "+signal+" ”");
					setup["hint"] = HINTTYPE_WALK;
				}
				else
					return tell(me, "目前"+pnoun(2, me)+"是攻擊方，無法對投手下達暗號。\n");
					
				break;
	
			default:
				return tell(me, "沒有 "+arg+" 這種暗號種類。\n");
		}
		
		
		
		if( setup["hinttimes"] == 0 )
			tell(me, pnoun(2, me)+"這次球賽的暗號下達次數已達上限。\n");
		else
			tell(me, pnoun(2, me)+"這場球賽剩下 "+setup["hinttimes"]+" 次下達暗號的機會。\n");

		BASEBALL_D->set_setup(myid, setup);
		return;
	}
			
	return tell(me, "請輸入正確的指令格式(help baseball)。\n");
}
