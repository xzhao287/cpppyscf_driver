import csv
from pyscf import gto, scf, qmmm, grad

atoms = []
coords = []
charges = []

with open('_cp2k_small.pdb', 'r') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=" ", skipinitialspace=True)
    for line in csv_reader:
        if int(line[4]) == 1:
            atoms.append([line[-2], (float(line[5]), float(line[6]), float(line[7]))])
        else:
            coords.append((float(line[5]), float(line[6]), float(line[7])))
            charges.append(float(line[-1]))
    print(atoms)
    print(coords)
    print(charges)

mol = gto.M(atom=atoms, basis='ccpvdz')
mf = qmmm.mm_charge(scf.RHF(mol), coords, charges)
mf.kernel()
mf.nuc_grad_method().run()
hfg = qmmm.mm_charge_grad(grad.RHF(mf), coords, charges).run()