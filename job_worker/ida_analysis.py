import idc
import idaapi
import binascii

idc.set_inf_attr(INF_AF, idc.get_inf_attr(INF_AF) | AF_DODATA)

print("Waiting for the end of the auto analysis...")
idc.auto_wait()
print("Autoanalysis done!")

dumped_netnode_value ='ca75b28848ea06bcae409699fa2510a03bbaf43bd167eecb17d52918187133a793ebf8d3270230c7164d7a79b53c2c3edd611ede975690784cf2c254abe8b587140d19a3f46b2be109bde1da1b7ed4d7c9f7b58135f2c296db4e86ad29b6f0b999b5599d40c3bae8b29d2cc06ecef63cba0e1b9a9505c1efe9019a7020127e100000000000000000000000000000000000000000000000000000000000000000'
idaapi.netnode('$ user1', 0, False).kill() # deleting netnode with plain text info
idaapi.netnode('$ original user', 0, False).supset(0, binascii.unhexlify(dumped_netnode_value))

idc.qexit(0)