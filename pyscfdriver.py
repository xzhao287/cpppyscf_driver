from pyscf import gto, scf, qmmm, grad
import numpy

def QMcalculation(pQMCoords, pQMKinds, pQMBasis, pQMMult, pQMCharge, pMMCoords, pMMCharges):

    print("pQMCoords", type(pQMCoords))
    print(pQMCoords)

    print("pQMKinds", type(pQMKinds))
    print(pQMKinds)

    print("pQMBasis", type(pQMBasis))
    print(pQMBasis)

    print("pQMMult", type(pQMMult))
    print(pQMMult)

    print("pQMCharge", type(pQMCharge))
    print(pQMCharge)

    print("pMMCharges", type(pMMCharges))
    print(pMMCharges)

    print("pMMCoords", type(pMMCoords))
    print(pMMCoords)

    atoms = []
    for qm_coord_temp, qm_element_temp in zip(pQMKinds, pQMCoords):
        qm_atom_temp = [qm_coord_temp] + qm_element_temp
        atoms.append(qm_atom_temp)

    mol = gto.M(atom=atoms, basis=pQMBasis)
    mf = qmmm.mm_charge(scf.RHF(mol), pMMCoords, pMMCharges)

    energy = mf.kernel()
    mf_grad = qmmm.mm_charge_grad(grad.RHF(mf), pMMCoords, pMMCharges)
    qmforce = mf_grad.kernel()

    print("energy = ", energy, type(energy))
    print("force", type(qmforce))
    print(qmforce)

    return energy, qmforce
