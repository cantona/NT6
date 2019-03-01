/******** Written by ken@NT.  All rights reserved. ********/
//ip.c
/**********************************************************/
/* 用法︰ 除了用(ip id)本指令來查知對方IP，或玩家所在地外 */
/*        還可以由外部調用convert_ip函數，比如logind.c    */
/*        調用方法，假設ob是一個玩家，那麼調用的方法如下  */
/*        "/cmds/adm/ip.c"->convert_ip(query_ip_number    */
/*        (ob)) 這樣就會返回一個字符串類型的ob的所在地。  */
/*                                                        */
/* 更新︰ 數據庫放在/adm/etc/ipdata/ 分別放著五個己分類   */
/*        的IP數據文件，如發現有未知IP，可以自行更新。    */
/*                                                        */
/* 準確︰ 準確度完全取決于數據庫，本程序是這樣實現IP查找  */
/*        的，一個IP由四個IP段所組成，A.B.C.D 先找到IP的  */
/*        A段，這決定在/ipdata/裡的那個文件中查找，大大加 */
/*        快了查找到速度，然後查找query_ip_number(ob)是否 */
/*        在和IP1和IP2之間是就反回後面的地區名，不是就找下*/
/*        一行，到最後也不到返回未知地區。( by ken@NT )   */
/**********************************************************/

#include <ansi.h>
inherit F_CLEAN_UP;

#define IP_DIR "/adm/etc/ipdata/" // IP數據所放的位置
#define EXT    ".ip" // 定義IP數據文件的副檔名

int help(object me);
int main(object me, string arg);

string convert_ip(string ip); // 給外部調用的函數

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string ip,output;
        object ob;

        if (!SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
                
        if (!arg || sscanf(arg, "%s", ip) != 1)
                return help(me);

        seteuid(geteuid(me));
        ob = UPDATE_D->global_find_player(arg);
        if (objectp(ob))
        {
                ip     = query_ip_number(ob); // 在玩家身上取得IP                               
                output = convert_ip(ip);
                UPDATE_D->global_destruct_player(ob, 1);
                write(output + "\n");
                return 1;
        }
        else
        {
                output = convert_ip(ip);
                write(output + "\n");
                return 1;
        }
}

string convert_ip(string ip)
{
        string  *ip_data_detail, *ip_data, *ip_detail;
        int a, b, c, d, i, count,  ipa, ipb, ipc, find = 0;
        
        if (!stringp(ip))
                return "";
        if (sscanf(ip, "%d.%d.%d.%d", a, b, c, d) != 4)
                return "";
        
        ip_detail = explode(ip, ".");
        // 把cut開做四段，如果IP= 127.0.0.1 那麼ip_detail[0] = 127                                 
        // ip_detail[1] = 0 ip_detail[2] = 0 ip_detail[3] = 1
        // 考慮到效率的問題，先判斷ip_detail[0]是什麼，再打開對應的IP文件
        // 當然IP文件要先經過分類(即是ip_detail[0].ip放著的所有IP都是以此開頭)
        if (file_size(IP_DIR + ip_detail[0] + EXT) > 0)
        {
                ip_data = explode(read_file(IP_DIR + ip_detail[0] + EXT), "\n");
        }
        
        else if (file_size(IP_DIR + "0" + EXT) > 0)
        { 
                ip_data = explode(read_file(IP_DIR + "0" + EXT), "\n");
        }

        sscanf(ip, "%d.%d.%d.%d", a, b, c, d);
        // 把IP每段強制性變為3個字符，比如 127.0.0.1 變成127.000.000.001
        ip_detail[0] = sprintf("%03d", a );
        ip_detail[1] = sprintf("%03d", b );
        ip_detail[2] = sprintf("%03d", c );
        ip_detail[3] = sprintf("%03d", d );
        
        ip     = implode(ip_detail, ".");
        sscanf(ip, "%d.%d.%d.%d", a, b, c, d); // 把IP的字串變成整數類型
        ipb = d + (c * 1000) + (b * 1000000); // 把尾三段的IP相加，用作下面的運算

        count  = sizeof (ip_data);
        count  = count - 1;

        if  (ip == "127.000.000.001")
        {
                return "本地機器";
                find = 1;
        }
        if (find != 1)
        {               
                for (i=0; i<=count; i++)
                {
                        ip_data_detail = explode(ip_data[i], "|");
                        if(strcmp (ip[0..2], ip_data_detail[0][0..2]) != 0 &&
                           strcmp (ip[0..2], ip_data_detail[1][0..2]) != 0)
                        continue; // 如果IP的第一段完全相等于IP文件裡的IP頭一段則執行下面代碼
                        {                       
                                sscanf(ip_data_detail[0], "%d.%d.%d.%d", a, b, c, d);
                                ipa = d + (c * 1000) + (b * 1000000);
                                // ipa 是記著IP1尾三段的IP相加後的值
                                sscanf(ip_data_detail[1], "%d.%d.%d.%d", a, b, c, d);
                                ipc = d + (c * 1000) + (b * 1000000);
                                // ipc 記著IP2尾三段的IP相加後的值
                                // 如果玩家的IP是在ipa 和 ipc 之間的，即執行下面代碼
                                if (ipb <= ipa || ipb >= ipc)
                                continue;                       
                                {                       
                                        return ip_data_detail[2]; // 傳回該IP的地區
                                        find = 1;
                                        break;
                                }
                        }
                }
        }

        if (find == 0)
                return "未知地區";

}

int help(object me)
{
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

格式 : ip <IP地址 | 在線玩家>

HELP);
return 1;
}