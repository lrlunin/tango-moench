# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'tango-moench'
copyright = '2025, Leonid Lunin'
author = 'Leonid Lunin'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['breathe',
              'sphinxcontrib.mermaid',
              'sphinx.ext.mathjax',
              'sphinx-mathjax-offline',
              'sphinxcontrib.bibtex'
             ]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

bibtex_bibfiles = ['refs.bib']

bibtex_reference_style = 'author_year'

bibtex_default_style = 'plain'

breathe_projects = {
    "tango-moenchzmq": "../doxygen/zmq",
    "tango-moenchcontrol": "../doxygen/control",
}
breathe_default_project = "tango-moenchzmq"


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']
html_theme_options = {
    'github_type': 'star',
    'github_user': 'lrlunin',
    'github_repo': 'tango-moench',
    'codecov_button': 'true'
}
html_favicon = '_static/favicon.svg'
