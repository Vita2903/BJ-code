# Initiation of Epithelial Wound Closure Simulations

## Description
This repository contains code for simulations related to the article submitted to the *Biophysical Journal* titled **"Initiation of Epithelial Wound Closure by an Active Instability at the Purse String."** 

## Repository Structure
This repository includes the following subfolders:

### `1_initial_samples`
Prepares tissue samples with a circular wound using periodic boundary conditions.

### `2_elastic_energy`
Slowly varies the wound’s radius and measures the potential
energy of the tissue to study how the elastic modulus k_2 relates to the tissue parameters k_A and p_0.

### `3_dynamics`
Simulates the tissue dynamics to determine whether the wound closes or remains open for a chosen set of parameters.

### `4_fast_slow`
Explores the fast and slow phases of wound closure, incorporating fluctuating junctional tensions due to stochasticity of myosin turnover and cell growth in the bulk.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.