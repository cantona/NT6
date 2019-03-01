// This program is a part of NT MudLIB

/*
DROP TABLE IF EXISTS `cards`;
CREATE TABLE `cards` (
  `card` varchar(20) NOT NULL default '',
  `password` varchar(20) NOT NULL default '',
  `money` int(11) default '0',
  `maketime` int(11) default '0',
  `makeid` varchar(10) NOT NULL default '',
  `sale` int(2) default '0',
  `paytime` int(11) default '0',
  `payid` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`card`),
  KEY `password` (`password`),
  KEY `money` (`money`),
  KEY `sale` (`sale`),
  KEY `payid` (`payid`)
) TYPE=MyISAM;
*/

#include <ansi.h>
#include "/adm/etc/database.h"

#define SN_LEN            16
public varargs int db_create_card(mixed ob, string CardSn, string CardPass, int money);

int clean_up() { return 1; }

protected int valid_caller()
{
#ifdef DEBUG
        return 1;
#else
        if (!previous_object() ||
            !is_root(previous_object()))
                return 0;
        else
                return 1;
#endif
}

void create()
{
        seteuid(ROOT_UID);
}

// 查詢 CARD 相關信息
public mixed db_query_card(string CardSn, string key)
{
        mixed  res;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(CardSn) || sizeof(CardSn) != 18 )
                return 0;

        if( !stringp(key) || key == "" )
                return 0;

        sql = sprintf("SELECT %s FROM %s WHERE card = \"%s\"",
                      key, CARD_TABLE, CardSn);

        res = DATABASE_D->db_fetch_row(sql);

        if (arrayp(res) && sizeof(res))
                return res[0];
        else
                return 0;
}

public mixed db_find_card(string key, mixed data)
{
        mixed ret;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(key) || key == "" || !data )
                return 0;

        if (intp(data))
                sql = sprintf("SELECT card FROM %s WHERE %s = %d",
                              CARD_TABLE, key, data);
        else if (stringp(data))
                sql = sprintf("SELECT card FROM %s WHERE %s = \"%s\"",
                              CARD_TABLE, key, data);
        else
                return 0;

        ret = DATABASE_D->db_all_query(sql);

        return ret;
}

public varargs int db_create_card(mixed ob, string CardSn, string CardPass, int money)
{
        mixed  ret;
        string sql;
        string id;

        if( !valid_caller() )
                return 0;

        if( objectp(ob) )
                id = query("id", ob);
        else
        if( stringp(ob) )
                id = ob;
        else
                return 0;

        if( !stringp(id) || id == "" )
                return 0;

        sql = sprintf("INSERT INTO %s SET card = \"%s\", password = \"%s\", money = %d, makeid = \"%s\", maketime = %d",
                      CARD_TABLE, CardSn, CardPass, money, id, time());

        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
                return 0;

        return ret;
}

public int db_make_card(object me, int amount, int ctype)
{
        string strtmpSn, strtmpPass;
        string strQZ, strPS;           //  卡號前綴，用以表示卡的類別面額
        int nCount, i;
        mixed res, ret;
        string sql;

        // 注冊碼組合序列
        string *codes = ({
               "A", "B", "C", "D", "E", "F", "G", "H", "I",
               "J", "K", "L", "M", "N", "O", "P", "Q", "R",
               "S", "T", "U", "V", "W", "X", "Y", "Z",
               "a", "b", "c", "d", "e", "f", "g", "h", "i",
               "j", "k", "l", "m", "n", "o", "p", "q", "r",
               "s", "t", "u", "v", "w", "x", "y", "z",
               "0", "1", "2", "3", "4", "5", "6", "7", "8",
               "9"
        });

        if( !valid_caller() )
                return 0;

        if( amount <= 0 )
                return 0;

        // 為保証數據存儲沒有問題，每次最多生成500個卡號
        if( amount > 500 )
        {
                write("為保証數據存儲沒有問題，每次最多生成500個卡號！\n");
                return 0;
        }

        if( !ctype )
        {
                write("請輸入卡號種類。" HIC + "10 OR 50 OR 100" + NOR "分別代表10RMB，50RMB和100RMB面額！\n");
                return 0;
        }

        // 必須輸入合法的卡號種類
        switch(ctype)
        {
        case 10:
                strQZ = "TE";
                strPS = "Te";
                break;

        case 50:
                strQZ = "FT";
                strPS = "Fi";
                break;

        case 100:
                strQZ = "HU";
                strPS = "Hu";
                break;

        default:
                write("請輸入卡號種類。" HIC + "10 OR 50 OR 100" + NOR "分別代表10RMB，50RMB和100RMB面額！\n");
                return 0;
                break;
        }

        // 初始化
        strtmpSn = "";
        nCount = 0;
        res = ({});
        while(1)
        {
                // 卡號生成完畢，進行後續處理
                if( nCount >= amount )
                {
                        for (i = 0; i < sizeof(res); i+=2)
                        {
                                reset_eval_cost();
                                if( !db_create_card(me, res[i], res[i+1], ctype) )
                                {
                                        write("生成卡號時失敗！\n");
                                        return 0;
                                }
                                log_file("static/cards", sprintf("Card: %s-%s，value = %d.\n", res[i], res[i+1], ctype));
                        }
                        return 1;
                }

                // 產生一個隨機卡號
                strtmpSn = strQZ; // 卡號前綴
                strtmpPass = strPS;
                for(i = 0; i < SN_LEN; i ++)
                {
                        strtmpSn += codes[random(sizeof(codes))];
                        strtmpPass += codes[random(sizeof(codes))];
                }
/*
                sql = sprintf("SELECT card FROM %s WHERE card = \"%s\"",
                              CARD_TABLE, strtmpSn);
                ret = DATABASE_D->db_query(sql);
                if( ret ) continue; // 數據庫已經存在
                sql = sprintf("SELECT password FROM %s WHERE password = \"%s\"",
                              CARD_TABLE, strtmpPass);
                ret = DATABASE_D->db_query(sql);
                if( ret ) continue; // 數據庫已經存在
*/
                nCount ++;
                res += ({ strtmpSn, strtmpPass });
        }
}

// 設定卡號屬性
public int db_set_card(string CardSn, string key, mixed data)
{
        mixed  ret;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(key) || key == "" )
                return 0;

        if( intp(data) )
                sql = "UPDATE cards SET " + key + "=" + data + " WHERE card = '" + CardSn + "'";
        else if (stringp(data))
                sql = "UPDATE cards SET " + key + "=" + DB_STR(data) + " WHERE card = '" + CardSn + "'";
        else
                return 0;

        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
                return 0;

        return ret;
}

public int db_card_pay(object me, string CardSn, string CardPass)
{
        string strQZ, pass;
        int value, money;
        mixed res, ret;
        string sql;

        if( !objectp(me) ) return -1;

        if (time() - query_temp("last_try_card_pay", me) < 5 )
        {
                write("你距離上次充值錯誤的時間不足5秒，請稍微再試。\n");
                return 0;
        }

        if( !CardSn || sizeof(CardSn) != SN_LEN+2 )
        {
                write("充值卡號位數錯誤，請確認你的充值卡號的正確性。\n");
                set_temp("last_try_card_pay", time(), me);
                return 0;
        }

        strQZ = CardSn[0..1];
        switch(strQZ)
        {
        case "TE":
                break;
        case "FT":
                break;
        case "HU":
                break;
        default:
                write("充值卡號錯誤，請確認你的充值卡號的正確性。\n");
                set_temp("last_try_card_pay", time(), me);
                return 0;
                break;
        }

        res = DATABASE_D->do_sql("select password, money from cards where card = '" + CardSn + "'");

        if( !arrayp(res) || !stringp(pass = res[0]) )
        {
                write("充值卡號錯誤，請確認你的充值卡號的正確性。\n");
                return 0;
        }

        if( CardPass != pass )
        {
                write("充值卡密碼錯誤，請確認你的充值卡密碼的正確性。\n");
                return 0;
        }

        value = res[1];

        // 活動期間
        money = value + value / 5;

        // 處理卡沖值後標記
        sql = "UPDATE cards SET sale = 1, paytime = " + time() + ", payid = " + DB_STR(query("id", me)) + " WHERE card = '" + CardSn + "'";
        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
        {
                write(HIR "充值失敗(0000)，並盡快與ADMIN聯系。\n" NOR);
                return 0;
        }

        if( MEMBER_D->is_member(me) )
                MEMBER_D->db_pay_member(me, money);
        else
                MEMBER_D->db_create_member(me, money);


        tell_object(me, HIG "恭喜！王者幣(NT)充值成功，充值面額" + HIR + sprintf("%d", value) +
                        HIG "元，獲得 " + HIR + sprintf("%d", money) + HIG + " 王者幣(NT)。\n" NOR);
        return 1;
}
